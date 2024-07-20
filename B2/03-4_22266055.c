/**
 * @file   03-4_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int comparisons;  // 比較回数
    int substitutions;  // 代入回数
} Features;


/**
 * @brief 配列をバブルソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 * @param features ソートの比較回数・代入回数を入れる構造体
 */
void bubble_sort_array(int array[], int n, Features *features){
    int tmp,hikaku=0,dainyu=0;
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;j--){
            hikaku++;
            if(array[j]<array[j-1]){
                tmp=array[j];
                array[j]=array[j-1];
                array[j-1]=tmp;
                dainyu+=3;
            }
        }
    }

    features->comparisons = 0;  for(int k=0;k<hikaku;k++)features->comparisons++;
    features->substitutions = 0;  for(int l=0;l<dainyu;l++)features->substitutions++;
}

/**
 * @brief 配列を選択ソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 * @param features ソートの比較回数・代入回数を入れる構造体
 */
void selection_sort_array(int array[], int n, Features *features){
    int min_index,tmp,hikaku=0,dainyu=0;
    for(int i=0;i<n-1;i++){
        min_index=i;
        for(int j=i+1;j<n;j++){
            hikaku++;
            if(array[j]<array[min_index]){
                min_index=j;
                dainyu++;
            }
        }
        tmp=array[min_index];
        array[min_index]=array[i];
        array[i]=tmp;
    }

      features->comparisons = 0;  for(int k=0;k<hikaku;k++)features->comparisons++;
      features->substitutions = 0;  for(int l=0;l<dainyu;l++)features->substitutions++;
}

/**
 * @brief 配列を挿入ソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 * @param features ソートの比較回数・代入回数を入れる構造体
 */
void insertion_sort_array(int array[], int n, Features *features){
    int i,j,tmp,hikaku=0,dainyu=0;
    for(i=1;i<n;i++){
        tmp=array[i];
        hikaku++;
        for(j=i;j>1,array[j-1]>tmp;j--,hikaku++){
            array[j]=array[j-1];
            dainyu++;
        }
        array[j]=tmp;
    }
    
    features->comparisons = 0;  for(int k=0;k<hikaku;k++)features->comparisons++;
    features->substitutions = 0;  for(int l=0;l<dainyu;l++)features->substitutions++;
}

/**
 * @brief 配列をシェルソートで昇順に並び替える関数
 * @param array 並び替える配列
 * @param n 配列の要素数
 * @param features ソートの比較回数・代入回数を入れる構造体
 */
void shell_sort_array(int array[], int n, Features *features){
    int gap=1,i,j,tmp,hikaku=0,dainyu=0;
    while(gap<n/3){
        gap=gap*3+1;
        dainyu++;
    }
    while(gap>=1){
        for (i=gap;i<n;i++){
            tmp=array[i];
            j=i;
            hikaku++;
            while (j>=gap && array[j-gap]>tmp){
                array[j]=array[j-gap];
                j-=gap;
                dainyu++;
            }
            array[j]=tmp;
        }
        gap/=3;
    }

    features->comparisons = 0;  for(int k=0;k<hikaku;k++)features->comparisons++;
    features->substitutions = 0;  for(int l=0;l<dainyu;l++)features->substitutions++;
}

int main(void){
    // 入力処理ここから
    int *array[4];
    int n, i;
    Features features;
    scanf("%d", &n);
    for(i=0; i<4; i++){
        array[i] = (int *)malloc(n*sizeof(int));
    }
    for(i=0; i<n; i++) {
        scanf("%d", &array[0][i]);
    }
    // 入力処理ここまで
    
    // 各アルゴリズム用に配列をコピー
    for(i=1; i<4; i++) {
        memcpy(array[i], array[0], n*sizeof(int));
    }
    
    for (i=0; i<4; i++){
        if (i == 0) {
            bubble_sort_array(array[i], n, &features);  // バブルソート
            printf("Bu: %d %d\n", features.comparisons, features.substitutions);
        } else if (i == 1) {
            selection_sort_array(array[i], n, &features);  // 選択ソート
            printf("Se: %d %d\n", features.comparisons, features.substitutions);
        } else if (i == 2) {
            insertion_sort_array(array[i], n, &features);  // 挿入ソート
            printf("In: %d %d\n", features.comparisons, features.substitutions);
        } else if (i == 3) {
            shell_sort_array(array[i], n, &features);  // シェルソート
            printf("Sh: %d %d\n", features.comparisons, features.substitutions);
        }
    }
    
    for(i=0; i<4; i++) {
        free(array[i]);
    }

    return 0;
}
