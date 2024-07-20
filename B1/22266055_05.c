#include<stdio.h>
#define SIZE 10

void Bsort(int data[],int size){
    int i,j,tem;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(data[j]>data[j+1]){
                tem=data[j];
                data[j]=data[j+1];
                data[j+1]=tem;
            }
        }
    }
}

void printArray(int ar[],int size){
    int i;
    for(i=0;i<size;i++){
        printf("%4d",ar[i]);
    }
    printf("\n");
}

int main(void){
    int i;
    int data[SIZE];

    for(i=0;i<SIZE;i++){
        scanf("%d",&data[i]);
    }
    printf("before:");
    printArray(data,SIZE);
    Bsort(data,SIZE);
    printf(" after:");
    printArray(data,SIZE);
    return 0;
}