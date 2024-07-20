/**
 * @file   02-1_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 配列をバブルソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
 void bubble_sort_array(int array[], int n){
    int tmp;
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;j--){
            if(array[j]<array[j-1]){
                tmp=array[j];
                array[j]=array[j-1];
                array[j-1]=tmp;
            }
        }
    }
}

int main(void){
    // 入力処理ここから
    int *array; 
    int n, i;
    scanf("%d", &n);
    array = (int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    scanf("%d", &array[i]);
    // 入力処理ここまで
  
    bubble_sort_array(array, n);  // バブルソート
    
    // 出力処理ここから
    for(i=0; i<n; i++) {
        if(i>0) putchar(' ');
        printf("%d", array[i]);
    }
    putchar('\n');
    // 出力処理ここまで
  
    free(array);
    return 0;
}
