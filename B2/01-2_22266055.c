/**
 * @file   01-2_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 配列からの二分探索をする関数
 * @param array 探索する配列
 * @param n 配列の要素数
 * @param x 配列から探索する値
 * @return int xの位置（xが存在しないときは-1）
 */
int binary_search_array(int array[], int n, int x){
    int low,high,middle;
    low = 0;
    high = n-1;
    while(low<=high){
        middle = (low+high)/2;
        if(x == array[middle])return middle;
        if(x < array[middle])high = middle-1;
        if(x > array[middle])low = middle+1;
    }
    return -1;
}

int main(void){
    // 入力処理ここから
    int *array; 
    int n, x, i;
    scanf("%d", &n);
    array = (int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++) {
        scanf("%d", &array[i]);
    }
    scanf("%d", &x);
    // 入力処理ここまで
  
    int index = binary_search_array(array, n, x);  // 線形探索
  
    printf("%d\n", index);  // 出力処理

    free(array);
    return 0;
}
