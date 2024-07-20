#include <stdio.h>
#include <stdlib.h>

void downheap(int array[], int left, int right);
void heap_sort_array(int array[], int n);

int main(void){
    int n, i, *array;
    scanf("%d", &n);
    if ((array = (int *)malloc(n*sizeof(int))) == NULL) {
        printf("メモリが足りません\n");
        exit(1);
    }
    for(i=0; i<n; i++) scanf("%d", &array[i]);

    heap_sort_array(array, n);  // ヒープソート

    for(i=0; i<n; i++) {
        if(i>0) putchar(' ');
        printf("%d", array[i]);
    }
    putchar('\n');

    free(array);
    return 0;
}

/**
 * @brief array[left]からarray[right]の要素をヒープ化する関数
 * @param array 配列
 * @param left 左側の添字
 * @param right 右側の添字
 */
void downheap(int array[], int left, int right){
    int tmp;
    while(2*left+1 <= right){
        if(array[2*left+1] <= array[2*left+2] || 2*left+2 > right){
            if(array[left] > array[2*left+1]){
                tmp = array[left];
                array[left] = array[2*left+1];
                array[2*left+1] = tmp;
                left = 2*left+1;
            }else{
                return;
            }
        }else{
            if(array[left] > array[2*left+2]){
                tmp = array[left];
                array[left] = array[2*left+2];
                array[2*left+2] = tmp;
                left = 2*left+2;
            }else{
                return;
            }
        }
    }
}

/**
 * @brief 配列をヒープソートで「降順」に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void heap_sort_array(int array[], int n){
    int tmp;
    for(int i=(n-2)/2; i>=0; i--){
        downheap(array, i, n-1);
    }
    for(int l=n-1; l>0; l--){
        tmp = array[0];
        array[0] = array[l];
        array[l] = tmp;
        downheap(array, 0, l-1);
    }
}