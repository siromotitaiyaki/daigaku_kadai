#include<stdio.h>
#include<stdlib.h>
int main(void){
    int i,j,N;
    int **twoDimArray;
    printf("N=");
    scanf("%d",&N);
    twoDimArray=(int*)malloc(N*sizeof(int*));
    for(i=0;i<N;i++){
        twoDimArray[i]=(int*)malloc(N*sizeof(int));
        twoDimArray[i][j]=NULL;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("(%d,%d)=",i+1,j+1);
            scanf("%d",&twoDimArray[i][j]);
        }
    }
    for(i=0;i<N;i++){
        printf("(");
        for(j=0;j<N;j++){
            if(i>j){
                twoDimArray[i][j]=0;
            }
            printf("%d ",twoDimArray[i][j]);
        }
        printf(")\n");
    }
    for(i=0;i<N;i++){
        free(twoDimArray[i]);
    }
    free(twoDimArray);
    return 0;
}