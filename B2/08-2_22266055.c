#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    int age;  // 年齢
} Person;

typedef struct cell_ {
    struct cell_ *next; // 次のセルへのポインタ
    Person data;  // 値
} Cell;

Cell *make_cell(Person data);
void delete_all_cells(Cell *dummy);
void print_all_cells(Cell *dummy);
void print_all_cells_for_debug(Cell *cell, bool is_dummy);
Cell *merge_sort_cell(Cell *cell);
Cell *merge_list(Cell *c1, Cell *c2);

int main(void) {
    Cell *dummy;  // ダミーセルのポインタ
    Cell *tail;  // 常に末尾のセルを指すポインタ
    Person dummy_data = {0};
    Person input;
    int n, i;
    
    dummy = make_cell(dummy_data);
    
    // 入力処理ここから
    scanf("%d", &n);
    tail = dummy;
    for(i=0; i<n; i++) {
        scanf("%s %d", input.name, &input.age);
        tail->next = make_cell(input);
        tail = tail->next;
    }
    
    // 入力処理ここまで
    dummy->next = merge_sort_cell(dummy->next);  // マージソート
    print_all_cells(dummy);  // 出力処理
    
    // 後処理ここから
    delete_all_cells(dummy);
    free(dummy);
    // 後処理ここまで
    return 0;
}

/**
 * @brief セルを作成して返す関数
 * @param data Person型のデータ
 * @return dataを持ったセル
 */
Cell *make_cell(Person data) {
    Cell *cell = (Cell *)malloc(sizeof(Cell));
    if (cell == NULL) {
        printf("メモリが足りません");
        exit(1);
    }
    cell->data = data;
    cell->next = NULL;
    return cell;
}

/**
 * @brief 全てのセルを削除する関数
 * @param dummy 連結リストのダミーセルのポインタ
 */
void delete_all_cells(Cell *dummy) {
    Cell *delete_cell;
    while (dummy->next != NULL) {
        delete_cell = dummy->next;
        dummy->next = dummy->next->next;
        free(delete_cell);
    }
}

/**
 * @brief 単方向リストのマージソートをする関数
 * @param cell 連結リストの先頭を指すポインタ
 * @param 整列済みの連結リストの先頭を指すポインタ
 */
Cell *merge_sort_cell(Cell *cell){
    if(cell == NULL || cell->next == NULL){
        return cell;
    }
    Cell *slow = cell;
    Cell *fast = cell->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    Cell *second_half = slow->next;
    slow->next = NULL;
    Cell *first = merge_sort_cell(cell);
    Cell *second = merge_sort_cell(second_half);
    return merge_list(first, second);
}

/**
 * @brief 単方向リストをマージする
 * @param c1 整列済み連結リスト1の先頭を指すポインタ
 * @param c2 整列済み連結リスト2の先頭を指すポインタ
 * @return マージ済みの連結リストの先頭を指すポインタ
 * @note 先頭への挿入・先頭以外への挿入の両方を行うため、
 *       ダミーセルを使うとマージ済みの連結リストの実装が容易ですが、
 *       「マージ済みの連結リストの先頭を指すポインタ」を返すことに注意してください
 */
Cell *merge_list(Cell *c1, Cell *c2){
    Cell *dummy = make_cell((Person){0});
    Cell *current = dummy;
    while(c1 != NULL && c2 != NULL){
        if(c1->data.age <= c2->data.age){
            current->next = c1;
            c1 = c1->next;
        }else{
            current->next = c2;
            c2 = c2->next;
        }
        current = current->next;
    }
    if(c1 != NULL){
        current->next = c1;
    }else{
        current->next = c2;
    }
    Cell *merged_list = dummy->next;
    free(dummy);
    return merged_list;
}

/**
 * @brief セルの値を先頭から順にスペース区切りで表示する関数
 * @param dummy 連結リストのダミーセルのポインタ
 */
void print_all_cells(Cell *dummy) {
  Cell *current = dummy->next;
  while (current != NULL) {
    printf("%s %d\n", current->data.name, current->data.age);
    current = current->next;
  }
}

/**
 * @brief セルの値などを表示するデバッグ用関数
 * @param cell 連結リストのセルのポインタ
 * @param is_dummy cellが連結リストのダミーセルのポインタのとき、true
 *                 cellが連結リストの先頭セルを指すポインタのとき、false
 * @note デバッグ用にエラー出力となっているので、提出時に残っていても採点には影響しません
 */
void print_all_cells_for_debug(Cell *cell, bool is_dummy){
  Cell *current;
  if (is_dummy) {
      current = cell->next;
  } else {
      current = cell; 
  }
  fprintf(stderr, "-- Debug begin -----\n");
  while (current != NULL) {
    fprintf(stderr, "%s %d\n", current->data.name, current->data.age);
    current = current->next;
	}
  fprintf(stderr, "-- Debug end -------\n");
}