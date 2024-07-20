#include<stdio.h>
#define num 31
int main(void){
    int n,k=1;
    long int F[4];
    F[0]=3; F[1]=0; F[2]=2;
    for(n=3;;n++){
        F[3]=F[1]+F[0];
        if(F[3]%n==0){
            k++;
            if(k>=num)break;
            printf("k=%d\n",n);
            printf("F[k]=%ld\n",F[3]);
        }
        F[0]=F[1]; F[1]=F[2]; F[2]=F[3];
    }
    printf("k=%d\n",n);
    printf("F[k]=%ld\n",F[3]);
    return 0;
}