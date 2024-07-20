/**
 * @file   03-3_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @brief 配列をシェルソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 */
void shell_sort_array(int array[], int n){
    int gap=1,i,j,tmp;
    while(gap<n/3){
        gap=gap*3+1;
    }
    while (gap>=1){
        for (i=gap;i<n;i++) {
            tmp=array[i];
            j=i;
            while (j>=gap && array[j-gap]>tmp) {
                array[j]=array[j-gap];
                j-=gap;
            }
            array[j]=tmp;
        }
        gap/=3;
    }
}

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
    
    shell_sort_array(array, n);  // シェルソート
    
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
