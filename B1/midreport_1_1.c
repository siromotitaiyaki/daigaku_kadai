#include<stdio.h>
#include<stdlib.h>
void max(int M,int count[]){
    int i,j,tmp=0;
    int *equal;
    equal=malloc((M+1)*sizeof(int*));
    for(i=1;i<M;i++){
        if(count[tmp]<count[i]){
            tmp=i;
            for(j=0;j<=i;j++)equal[j]=NULL;
            j=0;
        }else if(count[tmp]==count[i]){
            equal[j]=i;
            j++;
        }
    }
    printf("%d",tmp);
    for(j=0;j<M;j++){
        if(equal[j]!=NULL){
            printf(",%d",equal[j]);
        }else break;
    }
}
int main(void){
    int M,n;
    int tmp;
    int *N;
    int *count;
    printf("M:");
    scanf("%d",&M);
    N=malloc((M+1)*sizeof(int*));
    count=malloc(M*sizeof(int*));
    for(n=0;n<M;n++){
        N[n]=0;
        count[n]=0;
    }
    for(n=0;n<M;n++){
        printf("N[%d]:",n+1);
        scanf("%d",&N[n]);
        tmp=N[n];
        count[tmp]++;
    }
    max(M,count);
    printf("\n");
    free(N);
    return 0;
}