/**
 * @file   02-4_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    char class;  // クラス
} Student;


/**
 * @brief 構造体Studentの配列をclassについて選択ソートで昇順に並び替える関数
 * @param array 探索する構造体の配列
 * @param n 配列の要素数
 */
void selection_sort_student(Student array[], int n){
    int min_index;
    Student tmp;
    for(int i=0;i<n-1;i++){
        min_index=i;
        for(int j=i+1;j<n;j++){
            if(array[j].class<array[min_index].class){
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
    Student *array;
    int n, i;
    char x[MAX_NAME_LENGTH];
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
    
    selection_sort_student(array, n);  // 選択ソート
    
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
