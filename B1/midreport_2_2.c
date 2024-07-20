#include<stdio.h>
#include<math.h>
#include<time.h>
#define N 202212
int main(void){
    long int n;
    int i=0,j,k,l;
    int count=0;
    long int F[4];
    char text[5];
    int num[5];
    clock_t start,end;
    start=clock();
    F[0]=3; F[1]=0; F[2]=2;
    for(n=3;n<N;n++){
        F[3]=F[1]+F[0];
        F[3]%=(int)pow(10,5);
        sprintf(text,"%ld",F[3]);
        for(j=0;j<5;j++){
            num[j]=text[j]-'0';
        }
        for(l=0;l<5;l++){
        if(num[l]==2||num[l]==3||num[l]==5||num[l]==7){
            count++;
            if(count==5)i++;
        }
        }count=0;
        F[0]=F[1]; F[1]=F[2]; F[2]=F[3];
    }
    end=clock();
    printf("%d\n",i);
    printf("time:%f\n",(double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}