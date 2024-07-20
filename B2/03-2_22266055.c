/**
 * @file   03-2_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 配列を挿入ソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void insertion_sort_array(int array[], int n){
    int i,j,tmp;
    for(i=1;i<n;i++){
        tmp=array[i];
        for(j=i;j>1,array[j-1]>tmp;j--){
            array[j]=array[j-1];
        }
        array[j]=tmp;
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
    
    insertion_sort_array(array, n);  // 挿入ソート
    
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
