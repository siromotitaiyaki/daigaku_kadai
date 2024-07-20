#include<stdio.h>
#include<stdlib.h>
#define ARRAY_SIZE 3

int main(){
    int *piData=NULL;
    int i=0;

    piData=(int *)calloc(3,sizeof(int));
    if(piData==NULL){
        return -1;
    }
    *(piData+0)=10;
    *(piData+1)=20;
    *(piData+2)=30;

    for(i=0;i<ARRAY_SIZE; i++){
        printf("piData[%d]の値:%d\n",i,*(piData+i));
    }

    piData[0]=100;
    printf("piData[0]の値:%d\n",*(piData+0));

    return 0;
}