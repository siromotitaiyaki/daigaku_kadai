#include <stdio.h>
#include <string.h>
#define SIZE 10
#define LENGTH 30 

void strSort(char data[SIZE][LENGTH+1], int size){
    int i,j;
    char tmp[LENGTH+1];
    for(i=0;i<SIZE;i++){
        for(j=1;j<SIZE-i;j++){
            if(strcmp(data[i],data[i+j])>0){
                strcpy(tmp,data[i]);
                strcpy(data[i],data[i+j]);
                strcpy(data[i+j],tmp);
            }
        }
    }
}

void printStringArray(char data[SIZE][LENGTH+1], int size){
    int i;
    for(i=0;i<size;i++){
        printf("%s\n",data[i]);
    }
}

int main(void){
    int i,size = SIZE;
    char data[SIZE][LENGTH+1];
    char tmp[LENGTH+1];
    for(i=0;i<SIZE;i++){
        if(scanf("%s",data[i]) == EOF){
            size = i;
            break;
        }
    }
    printf("before:\n");
    printStringArray(data,size);
    printf("\n");

    strSort(data, size);

    printf("after:\n");
    printStringArray(data, size);
    return 0;
}