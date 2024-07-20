#include <stdio.h>
#include <stdlib.h>

void quick_sort_array(int array[], int n);
void quick_sort_recursion(int array[], int left, int right);
void print_all_array_for_debug(int array[], int left, int right, int pivot);

int main(void){
    // 入力処理ここから
    int *array; 
    int n, i;
    scanf("%d", &n);
    array = (int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++) {
        scanf("%d", &array[i]);
    }
    // 入力処理ここまで
    
    quick_sort_array(array, n);  // クイックソート
  
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

/**
 * @brief 配列をクイックソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void quick_sort_array(int array[], int n){
    quick_sort_recursion(array, 0, n-1);
}

/**
 * @brief 配列をクイックソートで昇順に並び替える再帰関数
 * @param array 並び替える配列
 * @param left 先頭の添字
 * @param right 末尾の添字
 */
void quick_sort_recursion(int array[], int left, int right){
    if(left<right){
        int pivot = array[left];
        int pl=left, pr=right;
        while(pl<=pr){
            while(array[pl]<=pivot && pl<=pr)pl++;
            while(pivot<=array[pr] && pl<=pr)pr--;
            if(pl<pr){
                int tmp = array[pl];
                array[pl] = array[pr];
                array[pr] = tmp;
            }
        }
        int tmp = array[left];
        array[left] = array[pr];
        array[pr] = tmp;
        quick_sort_recursion(array, left, pr-1);
        quick_sort_recursion(array, pr+1, right);
    }
}

/**
 * @brief 配列の要素の値などを表示するデバッグ用関数
 * @param array 並び替える配列
 * @param left 先頭の添字
 * @param right 末尾の添字
 * @param pivot 枢軸の値
 * @note デバッグ用にエラー出力となっているので、提出時に残っていても採点には影響しません
 */
void print_all_array_for_debug(int array[], int left, int right, int pivot){
    fprintf(stderr, "pivot=%d, array[%d]~array[%d]: [", pivot, left, right);
    for (int i=left; i<right+1; i++) {
        if (i>left) fprintf(stderr, " ");
        fprintf(stderr, "%d", array[i]);
    }
    fprintf(stderr, "]\n");
}