#include<stdio.h>
int count=0;
int F(int n){
    count++;
    if(n==1||n==2){
        return 1;
    }
    return F(n-1)+F(n-2);
}
int main(void){
    int n;
    scanf("%d",&n);
    F(n);
    printf("%d %d",F(n),count);
    return 0;
}