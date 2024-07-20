#include<stdio.h>

int main(int argc, char *argv[]){
    int a = 2,b = 3;
    double c = 2.0;
    double a1 =0.0, a2 = 0.0, a3 = 0.0;

    a1=b/a;
    printf("a1=%f\n",a1);

    a2=(double)b/a;
    printf("a2=%f\n",a2);

    a3=b/c;
    printf("a3=%f\n",a3);

    return 0;
}