#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

typedef struct {
    pthread_mutex_t mutexCurrRow;
    pthread_mutex_t mutexMedians;
    sem_t* semMinMedian;
    int M;
    int N;
    int* matrix;
    float* medians;
    int currRow;
} ThreadArgs;

void initMatrix(int* matrix, int rows, int columns);
float calculateMedian(int* row, int columns);
void calculateMinMed(float* arrayMed, int size);
int* sortRow(int* row, int size);

void* findRowMedian(void* args) {
    ThreadArgs* tArgs = (ThreadArgs*)args;
    int localIndex;

    pthread_mutex_lock(&tArgs->mutexCurrRow);
    localIndex = tArgs->currRow++;
    pthread_mutex_unlock(&tArgs->mutexCurrRow);

    int* sortedRow = sortRow(&tArgs->matrix[localIndex * tArgs->M], tArgs->M);

    pthread_mutex_lock(&tArgs->mutexMedians);
    if (localIndex < tArgs->M) {
        tArgs->medians[localIndex] = calculateMedian(sortedRow, tArgs->M);
    }
    if (localIndex == tArgs->M - 1) {
        sem_post(tArgs->semMinMedian);
    }
    pthread_mutex_unlock(&tArgs->mutexMedians);

    free(sortedRow);
    pthread_exit(NULL);
}

void* findMinMed(void* args) {
    ThreadArgs* tArgs = (ThreadArgs*)args;
    sem_wait(tArgs->semMinMedian);
    calculateMinMed(tArgs->medians, tArgs->M);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Insert the N and M value, where N is the number of rows and M is the number of columns.\n");
        exit(0);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    ThreadArgs tArgs;
    tArgs.N = N;
    tArgs.M = M;
    tArgs.medians = malloc(M * sizeof(float));
    tArgs.matrix = malloc(M * N * sizeof(int));
    tArgs.currRow = 0;
    tArgs.semMinMedian = sem_open("/min_med", O_CREAT | O_EXCL, 0644, 0);

    if (tArgs.medians == NULL || tArgs.matrix == NULL || tArgs.semMinMedian == SEM_FAILED) {
        printf("Failed to allocate memory or create semaphore.\n");
        exit(1);
    }

    initMatrix(tArgs.matrix, N, M);

    pthread_t* threads = malloc(N * sizeof(pthread_t));

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, findRowMedian, (void*)&tArgs);
    }

    pthread_t thread_minMed;
    pthread_create(&thread_minMed, NULL, findMinMed, (void*)&tArgs);

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_join(thread_minMed, NULL);

    printf("The medians are:\n");
    for (int i = 0; i < M; i++) {
        printf("[%f]", tArgs.medians[i]);
    }
    printf("\n");

    sem_close(tArgs.semMinMedian);
    sem_unlink("/min_med");
    free(tArgs.matrix);
    free(tArgs.medians);
    free(threads);

    return 0;
}

void calculateMinMed(float* medians, int size) {
    float minMed = medians[0];

    for (int i = 1; i < size; i++) {
        if (minMed > medians[i]) {
            minMed = medians[i];
        }
    }

    printf("The min median is: %f\n", minMed);
}

float calculateMedian(int* row, int columns) {
    if (columns % 2 == 0) {
        int mid1 = columns / 2 - 1;
        int mid2 = columns / 2;
        return (row[mid1] + row[mid2]) / 2.0f;
    } else {
        int mid = columns / 2;
        return row[mid];
    }
}

int* sortRow(int* row, int size) {
    int* rowToReturn = malloc(size * sizeof(int));

    memcpy(rowToReturn, row, size * sizeof(int));

    printf("Ordered row: ");
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (rowToReturn[j + 1] < rowToReturn[j]) {
                int temp = rowToReturn[j];
                rowToReturn[j] = rowToReturn[j + 1];
                rowToReturn[j + 1] = temp;
            }
        }
    }

    for (int y = 0; y < size; y++) {
        printf("[%d]", rowToReturn[y]);
    }
    printf("\n");

    return rowToReturn;
}

void initMatrix(int* matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i * columns + j] = rand() % 100 + 1;
            printf("[%d]", matrix[i * columns + j]);
        }
        printf("\n");
    }
}
