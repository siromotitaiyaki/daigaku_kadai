#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    int num, tmp, i, j;
    clock_t start, end;
    srand((unsigned int)time(NULL));
    scanf("%d", &num);
    int n[num];
    for(i=0; i<num; i++){
        n[i] = rand() % num;
        printf("%d ", n[i]);
    }
    printf("\n");
    start = clock(); // 計測開始 //
    for(i=0; i<num; i++){ // バブルソート //
        for(j=0; j<num-1; j++){
            if(n[j+1] < n[j]){
                tmp = n[j+1];
                n[j+1] = n[j];
                n[j] = tmp;
            }
        }
    }
    end = clock(); // 計測終了 //
    for(i=0; i<num; i++){
        printf("%d ", n[i]);
    }
    printf("\n");
    printf("clock:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}