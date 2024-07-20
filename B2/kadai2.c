#include<stdio.h>
#include<math.h>
#define a (unsigned int)1103515245
#define c (unsigned int)12345
#define M (unsigned int)pow(2, 31)
#define X_0 (unsigned int)7654

int main(void){
    unsigned int X[2024] = {};
    X[0] = X_0; //初期値
    //(1)
    for(int i=0; i<2024; i++){ //漸化式計算
        X[i+1] = (a*X[i]+c) % M;
    }
    printf("X[2023] = %d\n", X[2023]);
    //(2-A)
    int X_A[2024] = {};
    printf("2-A:\n[");
    for(int i=0; i<2024; i++){ //偶奇判定
        X_A[i] = (int)(X[i] % (unsigned int)2);
        printf("%d", X_A[i]);
        if(i>=2023)break;
        printf(", ");
    }
    printf("]\n");
    //(2-B)
    int X_B[2024] = {};
    printf("2-B:\n[");
    for(int i=0; i<2024; i++){ //大小比較
        if(X[i] < M/(unsigned int)2){
            X_B[i] = 0;
        }else{
            X_B[i] = 1;
        }
        printf("%d", X_B[i]);
        if(i>=2023)break;
        printf(", ");
    }
    printf("]\n");
    return 0;
}