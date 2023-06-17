#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

typedef struct {
    int M;
    int N;
    int *matrix;
    float *medians;
    int currRow;
    pthread_mutex_t mutexCurrRow;
    pthread_mutex_t mutexMedians;
    sem_t* semMinMedian;
} ThreadArgs;


void initMatrix(int * matrix, int rows, int columns);
float calculateMedian(int* row, int columns);
void calculateMinMed(float* arrayMed, int size);
int* sortRow(int* row, int size);

void* findRowMedian(void* args){
    ThreadArgs *tArgs = (ThreadArgs*) args;
    int localIndex;
    pthread_mutex_lock(&tArgs->mutexCurrRow);
        localIndex = tArgs->currRow;
        tArgs->currRow++;
    pthread_mutex_unlock(&tArgs->mutexCurrRow);
    pthread_mutex_lock(&tArgs->mutexMedians);
        float median = calculateMedian(sortRow(&tArgs->matrix[localIndex*tArgs->M], tArgs->M), tArgs->M);
        if(localIndex <= tArgs->M){
            tArgs->medians[localIndex] = median;
        }
        if(localIndex == tArgs->M){
            sem_post(tArgs->semMinMedian);
        }
    pthread_mutex_unlock(&tArgs->mutexMedians);


    pthread_exit(NULL);
}

void* findMinMed(void* args){
    ThreadArgs *tArgs = (ThreadArgs*) args;
    sem_wait(tArgs->semMinMedian);
    calculateMinMed(tArgs->medians, tArgs->M);
    pthread_exit(NULL);
}

int main(int argc, char ** argv){

    if(argc < 3){
        printf("Insert the N and M value, where N is the num of the rows and M is the num of columns \n");
        exit(0);
    }
    ThreadArgs tArgs;
    tArgs.N = atoi(argv[1]);
    tArgs.M = atoi(argv[2]);
    tArgs.medians = malloc(tArgs.M * sizeof(float));
    tArgs.matrix = malloc(tArgs.M * tArgs.N * sizeof(int));
    tArgs.currRow = 0;
    tArgs.semMinMedian = sem_open("/min_med",0644, 0);
    initMatrix(tArgs.matrix, tArgs.N, tArgs.M);

    pthread_t* threads = malloc(tArgs.N * sizeof(pthread_t));

    for(int i = 0; i < tArgs.N; i++){
        pthread_create(&threads[i], NULL, findRowMedian, (void*)&tArgs);
    }
    pthread_t thread_minMed;
    pthread_create(&thread_minMed, NULL, findMinMed, (void*)&tArgs);

    for(int i = 0; i < tArgs.N; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_join(thread_minMed, NULL);

    printf("The medians are: \n");
    for(int i = 0; i < tArgs.M; i++){
        printf("[%f]", tArgs.medians[i]);
    }

    sem_close(tArgs.semMinMedian);
    free(tArgs.matrix);
    free(tArgs.medians);
    return 0;
}

void calculateMinMed(float* medians, int size){
    float minMed = medians[0];

    for(int i = 1; i < size; i ++){
        if(minMed > medians[i]){
            minMed = medians[i];
        }
    }
    printf("The min median is: %f\n", minMed);
}

float calculateMedian(int* row, int columns){
    if(columns % 2 == 0){
        int mid1 = columns / 2 -1;
        int mid2 = columns / 2;
        return (row[mid1] + row[mid2])/ 2;
    }else{
        int mid = columns /2;
        return row[mid];
    }
}

int* sortRow(int* row, int size){
    int* rowToReturn = malloc(size *sizeof(int));

    memcpy(rowToReturn, row, size*sizeof(int));

    printf("ordered row ->");
    for(int i = 0; i < size - 1; i++){
        for(int j= 0; j < size -i-1;j++){
            if(rowToReturn[j+1] < rowToReturn[j]){
                int temp= rowToReturn[j];
                rowToReturn[j] = rowToReturn[j+1];
                rowToReturn[j+1] = temp;
            }
        }
    }
    for(int y = 0; y< size; y++){
        printf("[%d]", rowToReturn[y]);
    }
    printf("\n");
    return rowToReturn;
}

void initMatrix(int* matrix, int rows, int columns){
    for(int i = 0; i < rows; i++){
        for(int j= 0; j < columns; j++){
            matrix[i*columns+j] = rand() % 100 + 1;
            printf("[%d]", matrix[i*columns+j]);
        }
        printf("\n");

    }
}