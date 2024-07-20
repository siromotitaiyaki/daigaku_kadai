/**
 * @file   03-1_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    char class;  // クラス
} Student;


/**
 * @brief 構造体Studentの配列をclassについてバブルソートで昇順に並び替える関数
 * @param array 探索する構造体の配列
 * @param n 配列の要素数
 */
void bubble_sort_student(Student array[], int n){
    Student tmp;
    for(int i=0;i<n-1;i++){
        int swap=0;
        for(int j=n-1;j>i;j--){
            if(array[j].class<array[j-1].class){
                tmp=array[j];
                array[j]=array[j-1];
                array[j-1]=tmp;
                swap=1;
            }
        }
        if(swap==0)break;
    }
}

int main(void){
    // 入力処理ここから
    Student *array;
    int n, i;
    scanf("%d", &n);
    array = (Student *)malloc(n*sizeof(Student));
    for(i=0; i<n; i++){
        scanf("%s", array[i].name);  // nameの入力
    }
    getchar();  // 改行文字の読み捨て
    for(i=0; i<n; i++){
        scanf("%c", &array[i].class);  // classの入力
        getchar();  // 空白文字の読み捨て
    }
    // 入力処理ここまで
  
    bubble_sort_student(array, n);  // バブルソート
  
    // 出力処理ここから
    for(i=0; i<n; i++) {
        if(i>0) putchar(' ');
        printf("%s", array[i].name);
    }
    putchar('\n');
    // 出力処理ここまで
    
    free(array);
    return 0;
}
