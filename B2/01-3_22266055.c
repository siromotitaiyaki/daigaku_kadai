/**
 * @file   01-3_template.c
 * @brief  Template program
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    int age;  // 年齢
} Person;


/**
 * @brief 構造体Personからの二分探索をする関数
 * @param array 探索する構造体の配列
 * @param n 配列の要素数
 * @param x 配列から探索するnameの値
 * @return int xと同じnameの値を持つ要素のage（xが存在しないときは-1）
 */
int binary_search_array(Person array[], int n, char x[]){
    int low,high,middle;
    low = 0;
    high = n-1;
    while(low<=high){
        middle = (low+high)/2;
        if(strcmp(x,array[middle].name)==0)return array[middle].age;
        if(strcmp(x,array[middle].name)<0)high = middle-1;
        if(strcmp(x,array[middle].name)>0)low = middle+1;
    }
    return -1;
}

int main(void){
    // 入力処理ここから
    Person *array;
    int n, i;
    char x[MAX_NAME_LENGTH];
    scanf("%d", &n);
    array = (Person *)malloc(n*sizeof(Person));
    for(i=0; i<n; i++){
        scanf("%s", array[i].name);  // nameの入力
    }
    for(i=0; i<n; i++){
        scanf("%d", &array[i].age);  // ageの入力
    }  
    scanf("%s", x);
    // 入力処理ここまで
    
    int index = binary_search_array(array, n, x);  // 二分探索
    
    printf("%d\n", index);  // 出力処理
    
    free(array);
    return 0;
}
