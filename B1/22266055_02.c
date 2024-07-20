#include<stdio.h>
int main(void){
    int a,b;
    scanf("%d",&b);
    for(a=1;a<=b;a++){
        if(a%3==0&&a%5==0){
            printf("FizzBuzz\n");
        }else if(a%3==0){
            printf("Fizz\n");
        }else if(a%5==0){
            printf("Buzz\n");
        }else{
            printf("%d\n",a);
        }
    }
    return 0;
}