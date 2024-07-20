#include <stdio.h>
#include <stdlib.h>

typedef struct cell_ {
  struct cell_ *next; // 次のセルへのポインタ
  int value;  // 値
} Cell;

Cell *make_cell(int num);
void delete_all_cells(Cell *dummy);
void print_all_cells(Cell *dummy);
void print_all_cells_for_debug(int pivot, Cell *dummy);
Cell *quick_sort_cell(Cell *cell);
Cell *concatenate_cell(Cell *cell1, Cell *cell2);

int main(void) {
    Cell *dummy;  // ダミーセルのポインタ
    Cell *tail;  // 常に末尾のセルを指すポインタ
    int num, n, i;
    
    dummy = make_cell(0);
    dummy->next = NULL;
    
    // 入力処理ここから
    scanf("%d", &n);
    tail = dummy;
    for(i=0; i<n; i++) {
        scanf("%d", &num);
        tail->next = make_cell(num);
        tail = tail->next;
    }
    // 入力処理ここまで
    dummy->next = quick_sort_cell(dummy->next);  // クイックソート
    print_all_cells(dummy);  // 出力処理
    
    // 後処理ここから
    delete_all_cells(dummy);
    free(dummy);
    // 後処理ここまで
    return 0;
}

/**
 * @brief セルを作成して返す関数
 * @param num セルの値
 * @return numという値を持ったセル
 */
Cell *make_cell(int num) {
    Cell *cell = (Cell *)malloc(sizeof(Cell));
    if (cell == NULL) {
        printf("メモリが足りません");
        exit(1);
    }
    cell->value = num;
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
 * @brief 単方向リストのクイックソートをする関数
 * @param cell 連結リストの先頭を指すポインタ
 * @param 整列済みの連結リストの先頭を指すポインタ
 */
Cell *quick_sort_cell(Cell *cell){
    if(cell == NULL || cell->next == NULL){
        return cell;
    }
    Cell *dummy1 = make_cell(0), *dummy2 = make_cell(0), *dummy3 = make_cell(0);
    Cell *left = dummy1;
    Cell *mid = dummy2;
    Cell *right = dummy3;
    int pivot = cell->value;
    while(cell != NULL){
        if(pivot > cell->value){
            left->next = make_cell(cell->value);
            left = left->next;
        }else if(pivot == cell->value){
            mid->next = make_cell(cell->value);
            mid = mid->next;
        }else if(pivot < cell->value){
            right->next = make_cell(cell->value);
            right = right->next;
        }
        cell = cell->next;
    }
    left = quick_sort_cell(dummy1->next);
    right = quick_sort_cell(dummy3->next);
    
    return concatenate_cell(concatenate_cell(left, dummy2->next), right);
}

/**
 * @brief 単方向リストを結合する関数
 * @param cell1 連結リスト1の先頭を指すポインタ
 * @param cell2 連結リスト2の先頭を指すポインタ
 * @return 結合後の連結リストの先頭を指すポインタ
 */
Cell *concatenate_cell(Cell *cell1, Cell *cell2){
    if(cell1 == NULL)return cell2;
    Cell *cell = cell1;
    while(cell->next != NULL){
        cell = cell->next;
    }
    cell->next = cell2;
    return cell1;
}

/**
 * @brief セルの値を先頭から順にスペース区切りで表示する関数
 * @param dummy 連結リストのダミーセル
 */
void print_all_cells(Cell *dummy) {
    int i=0;
    Cell *current = dummy->next;
    while (current != NULL) {
        if (i>0) putchar(' ');
        printf("%d", current->value);
        current = current->next;
        i++;
    }
    printf("\n");
    return;
}

/**
 * @brief セルの値などを表示するデバッグ用関数
 * @param dummy 連結リストのダミーセル
 * @note デバッグ用にエラー出力となっているので、提出時に残っていても採点には影響しません
 */
void print_all_cells_for_debug(int pivot, Cell *dummy){
    int i=0;
    Cell *current = dummy->next;
    fprintf(stderr, "pivot=%d: [", pivot);
    while (current != NULL) {
        if (i>0) fprintf(stderr, " ");
        fprintf(stderr, "%d",current->value);
        current = current->next;
		    i++;
    }
	  fprintf(stderr, "] ... number of cells: %d\n",i);
}