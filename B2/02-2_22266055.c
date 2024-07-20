/**
 * @file   02-2_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 配列を選択ソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void selection_sort_array(int array[], int n){
    int min_index,tmp;
    for(int i=0;i<n-1;i++){
        min_index=i;
        for(int j=i+1;j<n;j++){
            if(array[j]<array[min_index]){
                min_index=j;
            }
        }
        tmp=array[min_index];
        array[min_index]=array[i];
        array[i]=tmp;
    }
}

int main(void){
    // 入力処理ここから
    int *array; 
    int n, x, i;
    scanf("%d", &n);
    array = (int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    scanf("%d", &array[i]);
    // 入力処理ここまで
    
    selection_sort_array(array, n);  // 選択ソート
  
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
