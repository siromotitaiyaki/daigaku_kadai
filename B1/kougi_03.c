#include<stdio.h>
void rec(int no){
    if(no>0){
        rec(no-1);
        printf("%d",no);
        rec(no-2);
    }
}
int main(void){
    int n;
    scanf("%d",&n);
    rec(n);
    return 0;
}