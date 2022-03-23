#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define BUFF_SIZE 4096 //BUFFER INPUT SIZE
#define RES_SIZE 3 //RESULT SIZE
#define LIMIT 5 //MAX SIZE TO READ

int main(){
    char buff[BUFF_SIZE];
    char result[RES_SIZE];
    int n;
    printf("Insert two numbers or -1 to exit: \n");
    fflush(stdout);
    //READ FROM TERMINAL
    while( (n = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0 ){
        //IF THE FIRST NUMBER IS - 1 EXIT
        if(atoi(&buff[0]) == -1){
            exit(0);
        }
        //IF THE TWO NUMBERS ARE GREATER THAN 9 OR READS MORE THAN LIMIT
        if(atoi(&buff[0]) > 9 || atoi(&buff[2]) > 9 || n > LIMIT){
            printf("Invalid input\n");
            exit(0);
        }
        /*
            ATOI --> FROM CHAR INTO INT
            SPRINTF --> FROM INT TO CHAR
            THIS ROW CALCULATE THE RESULT
        */
        sprintf(result, "%d", (atoi(&buff[0])+atoi(&buff[2])));
        printf("The result is: ");
        fflush(stdout);
        //WRITE THE RESULT IN THE TERMINAL
        if(write(STDOUT_FILENO, &result, sizeof(result)) != sizeof(result)){
            printf("Write error!");
        }
        printf("\n");
        fflush(stdout);
    }
    if(n < 0){
        printf("Read error!");
    }
    exit(0);
}