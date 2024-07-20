#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

int buffer[MAX_ELEMENTS];

void merge_sort_array(int array[], int n);
void merge_sort_recursion(int array[], int left, int right);
void print_all_array_for_debug(int array[], int left, int right);

int main(void){
    // 入力処理ここから
    int *array; 
    int n, i;
    scanf("%d", &n);
    array = (int *)malloc(n*sizeof(int));
    for(i=0; i<n; i++)
    scanf("%d", &array[i]);
    // 入力処理ここまで 
  
    merge_sort_array(array, n);  // マージソート
    
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
 * @brief 配列をマージソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void merge_sort_array(int array[], int n){
    merge_sort_recursion(array, 0, n-1);
}

/**
 * @brief 配列をマージソートで昇順に並び替える再帰関数
 * @param array 並び替える配列
 * @param left 先頭の添字
 * @param right 末尾の添字
 */

void merge_sort_recursion(int array[], int left, int right){
    if(left<right){
        int mid = left+(right-left)/2;
        merge_sort_recursion(array, left, mid);
        merge_sort_recursion(array, mid+1, right);
        int i,j,k;
        int n1 = mid-left+1;
        int n2 = right+1;
        for(i=0; i<n1; i++){
            buffer[i] = array[left+i];
        }
        i=0;j=mid+1;k=left;
        while(i<n1 && j<n2){
            if (buffer[i] <= array[j]){
                array[k] = buffer[i];
                i++;
            }else{
                array[k] = array[j];
                j++;
            }k++;
        }
        while(i<n1){
            array[k] = buffer[i];
            i++;k++;
        }
        while(j<n2){
            array[k] = array[j];
            j++;k++;
        }
    }
}

/**
 * @brief 配列の要素の値などを表示するデバッグ用関数
 * @param array 並び替える配列
 * @param left 先頭の添字
 * @param right 末尾の添字
 * @note デバッグ用にエラー出力となっているので、提出時に残っていても採点には影響しません
 */
void print_all_array_for_debug(int array[], int left, int right){
    fprintf(stderr, "array[%d]~array[%d]: [", left, right);
    for (int i=left; i<right+1; i++) {
        if (i>left) fprintf(stderr, " ");
        fprintf(stderr, "%d", array[i]);
    }
    fprintf(stderr, "]\n");
}