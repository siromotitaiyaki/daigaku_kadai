#include <stdio.h>
#include <stdlib.h>

// #define ENABLE_UI // コメントアウトを外すとUIが表示されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#else
#define UI_PRINT(x) do {} while (0)
#endif

typedef struct cell_ {
    struct cell_ *next; // 次のセルへのポインタ
    int value;  // 値
} Cell;

typedef enum{
    INSERT     = 0,
    SEARCH     = 1,
    DELETE     = 2,
    DELETE_ALL = 3,
    PRINT_ALL  = 4,
} Mode;

Cell *make_cell(int num);
void insert_head(Cell **header, Cell *c);
Cell *search(Cell *header, int num);
int delete(Cell **header, int num);
void print_all_cells(Cell *header);
void delete_all_cells(Cell **header);

void print_not_found(int num);
void print_found(int num);
void print_empty();

int main(void) {
    int i, num, mode, value, deleted_result;
    Cell *cell, *header=NULL, *searched_cell;
    
	UI_PRINT("操作回数を入力してください。\n");
    
    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        UI_PRINT("[0 val] Insert, [1 val] Search, "
		"[2 val] Delete, [3 0] Delete All, [4 0] Print All:\n");
        scanf("%d %d", &mode, &value);

        // 操作
        switch (mode) {
        case INSERT:
            cell = make_cell(value);
            insert_head(&header, cell);
            break;

        case SEARCH:
            searched_cell = search(header, value);
            break;

        case DELETE:
            deleted_result = delete(&header, value);
            break;

        case DELETE_ALL:
            delete_all_cells(&header);
            break;
        }
    
        // 出力
        switch (mode) {
        case INSERT:
        case DELETE_ALL:
        case PRINT_ALL:
            print_all_cells(header);
            break;
            
        case SEARCH:
            if (searched_cell == NULL) {
                print_not_found(value);
            } else {
                print_found(value);	
            }
            break;

        case DELETE:
            if (deleted_result == -1) {
                print_not_found(value);
            } else {
                print_all_cells(header);
            }
            break;
        }
    }
    delete_all_cells(&header);
    return 0;
}

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

// 先頭にポインタcで指されたセルを挿入する関数
// note: headerは先頭を指すポインタとする
void insert_head(Cell **header, Cell *c) {
	c->next = *header;
    *header = c;
}

// 値がnumのセルを先頭から探索して返し、存在しなければNULLを返す関数
Cell *search(Cell *header, int num) {
	Cell *cell = header;
    while(cell != NULL){
        if(cell->value == num){
            return cell;
        }
        cell = cell->next;
    }
    return NULL;
}

// 値がnumのセルを先頭から探して削除し、成功時は0、失敗時は-1を返す関数
int delete(Cell **header, int num) {
	Cell *cell = *header;
    if(cell == NULL){
        return -1;
    }
    if(cell->value == num){
        *header = cell->next;
        return 0;
    }
    while(cell->next != NULL){
        if(cell->next->value == num){
            cell->next = cell->next->next;
            return 0;
        }
        cell = cell->next;
    }
    return -1;
}

void print_all_cells(Cell *header) {
    Cell *p = header;
    if (p == NULL) {
        printf("Empty\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    return;
}

void delete_all_cells(Cell **header) {
	while(*header != NULL){
        Cell *tmp = *header;
        *header = tmp->next;
        free(tmp);     
    }
}

void print_not_found(int num) {
    printf("Not Found %d\n", num);
}

void print_found(int num) {
    printf("Found %d\n", num);
}

void print_empty() {
    printf("Empty\n");
}
