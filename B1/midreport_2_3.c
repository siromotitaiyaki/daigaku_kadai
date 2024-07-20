#include<stdio.h>
#include<math.h>
#include<time.h>
#define M 3233514234548132
int main(void){
    long int m=M,i;
    long int Gm;
    clock_t start,end;
    start=clock();
    for(;;m=Gm){
        if(m%2==0){
            Gm=m/2;
        }else break;
    }
    for(i=3;i<=sqrt(m);i+=2,m=Gm){
        if(m%i==0){
            Gm=m/i;
        }
    }
    end=clock();
    printf("G(M)=%ld\n",Gm);
    printf("time:%f\n",(double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}