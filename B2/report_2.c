#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quick_sort(int array[], int left, int right);

int main(void){
    int num, i;
    clock_t start, end;
    srand((unsigned int)time(NULL));
    scanf("%d", &num);
    int n[num];
    for(i=0; i<num; i++){
        n[i] = i;
        printf("%d ", n[i]);
    }
    printf("\n");
    start = clock(); // 計測開始 //
    quick_sort(n, 0, num-1); // クイックソート //
    end = clock(); // 計測終了 //
    for(i=0; i<num; i++){
        printf("%d ", n[i]);
    }
    printf("\n");
    printf("clock:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}

void quick_sort(int array[], int left, int right){
    if(left < right){
        int pivot = array[left];
        int pl=left, pr=right;
        while(pl <= pr){
            while(array[pl] <= pivot && pl <= pr)pl++;
            while(pivot <= array[pr] && pl <= pr)pr--;
            if(pl < pr){
                int tmp = array[pl];
                array[pl] = array[pr];
                array[pr] = tmp;
            }
        }
        int tmp = array[left];
        array[left] = array[pr];
        array[pr] = tmp;
        quick_sort(array, left, pr-1);
        quick_sort(array, pr+1, right);
    }
}