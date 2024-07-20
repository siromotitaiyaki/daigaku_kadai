#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1

int main(void){
    int *array;
    int n, x, i, flag = 0;
    clock_t start, end;
    srand((unsigned int)time(NULL));
    scanf("%d", &n);
    array = (int*)malloc(n*sizeof(int));

    array[0] = 1;
    printf("%d ", array[0]);
    for(i=1; i<n; i++){
        array[i] = array[i-1] + (rand() % N) + 1;
        printf("%d ",array[i]);
    }
    printf("\n");

    scanf("%d", &x);

    start = clock();

    for(i=0; i<n; i++){
        if(array[i] == x){
            printf("%d\n", i);
            flag = 1;
            break;
        }
    }

    if(flag == 0)printf("Not Found:%d\n", x);

    end = clock();
    
    printf("clock:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

    free(array);
    return 0;
}