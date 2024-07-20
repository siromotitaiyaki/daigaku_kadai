#include<stdio.h>
void SumAndDifference(int *a,int *b){
    int i;
    i=*a; *a+=*b; *b=i-*b;
}

int main(void){
    int a,b;
    scanf("%d %d",&a,&b);
    SumAndDifference(&a,&b);
    printf("%d %d",a,b);
    return 0;
}