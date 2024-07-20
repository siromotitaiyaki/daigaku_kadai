#include <stdio.h>
#include <stdlib.h>

typedef struct cell_ {
    struct cell_ *prev; // 前のセルへのポインタ
    struct cell_ *next; // 次のセルへのポインタ
    int value;  // 値
} Cell;

Cell dummy;

typedef enum{
    INSERT_HEAD     = 0,
    INSERT_TAIL     = 1,
    SEARCH_FORWARD  = 2,
    SEARCH_BACKWARD = 3,
    DELETE_FORWARD  = 4,
    DELETE_BACKWARD = 5,
    DELETE_ALL      = 6,
    PRINT_ALL       = 7
} Mode;


Cell *make_cell(int num);
void insert_cell(Cell *c1, Cell *c2);
Cell *search_forward(Cell *dummy, int num);
Cell *search_backward(Cell *dummy, int num);
void delete_cell(Cell *c);
int delete_forward(Cell *dummy, int num);
int delete_backward(Cell *dummy, int num);
void print_all_cells(Cell *dummy);
void delete_all_cells(Cell *dummy);

void print_not_found(int num);
void print_found(int num);

int main(void) {
    int i, num, mode, value, deleted_result;
    Cell *cell ,*dummy, *searched_cell;

    // ダミーセルの作成
    dummy = make_cell(0);
    dummy->next = dummy;
    dummy->prev = dummy;

    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        scanf("%d %d", &mode, &value);

        // 操作
        switch (mode) {
        case INSERT_HEAD:
            cell = make_cell(value);
            insert_cell(dummy, cell);
            break;
            
        case INSERT_TAIL:
            cell = make_cell(value);
            insert_cell(dummy->prev, cell);
            break;

        case SEARCH_FORWARD:
            searched_cell = search_forward(dummy, value);
            break;

        case SEARCH_BACKWARD:
            searched_cell = search_backward(dummy, value);
            break;

        case DELETE_FORWARD:
            deleted_result = delete_forward(dummy, value);
            break;

        case DELETE_BACKWARD:
            deleted_result = delete_backward(dummy, value);
            break;

        case DELETE_ALL:
            delete_all_cells(dummy);
            break;
        }
    
        // 出力
        switch (mode) {
        case INSERT_HEAD:
        case INSERT_TAIL:
        case DELETE_ALL:
        case PRINT_ALL:
            print_all_cells(dummy);
            break;
            
        case SEARCH_FORWARD:
        case SEARCH_BACKWARD:
            if (searched_cell == NULL) {
                print_not_found(value);
            } else {
                print_found(value);	
            }
            break;

        case DELETE_FORWARD:
        case DELETE_BACKWARD:
            if (deleted_result == -1) {
                print_not_found(value);
            } else {
                print_all_cells(dummy);
            }
            break;
        }
    }
    delete_all_cells(dummy);
    free(dummy);  
    return 0;
}

// numという値を持ったセルを作成して返す関数
Cell *make_cell(int num) {
    Cell *cell = (Cell*)malloc(sizeof(Cell));
    cell->prev = NULL;
    cell->next = NULL;
    cell->value = num;
    return cell;
}

// ポインタc1で指されたセルの後に
// ポインタc2で指されたセルを挿入する関数
void insert_cell(Cell *c1, Cell *c2) {
    c2->next = c1->next;
    c1->next->prev = c2;
    c2->prev = c1;
    c1->next = c2;
}

// 値がnumのセルを先頭から探索して返し、
// 存在しなければNULLを返す関数
Cell *search_forward(Cell *dummy, int num) {
    Cell *current = dummy->next;
    while(current != dummy){
        if(current->value == num){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 値がnumのセルを末尾から探索して返し、
// 存在しなければNULLを返す関数
Cell *search_backward(Cell *dummy, int num) {
    Cell *current = dummy->prev;
    while(current != dummy){
        if(current->value == num){
            return current;
        }
        current = current->prev;
    }
    return NULL;
}

// ポインタcで指されたセルを削除する関数
void delete_cell(Cell *c) {
    c->prev->next = c->next;
    c->next->prev = c->prev;
    free(c);
}

// 値がnumのセルを先頭から探して削除し、
// 成功時は0、失敗時は-1を返す関数
int delete_forward(Cell *dummy, int num) {
    Cell *current = dummy->next;
    while(current != dummy){
        if(current->value == num){
            delete_cell(current);
            return 0;
        }
        current = current->next;
    }
    return -1;
}

// 値がnumのセルを末尾から探して削除し、
// 成功時は0、失敗時は-1を返す関数
int delete_backward(Cell *dummy, int num) {
    Cell *current = dummy->prev;
    while(current != dummy){
        if(current->value == num){
            delete_cell(current);
            return 0;
        }
        current = current->prev;
    }
    return -1;
}

// セルが存在するとき、セルの値を先頭から順にスペース区切りで表示し、
// セルが存在しないとき、Emptyを表示する関数
void print_all_cells(Cell *dummy) {
    Cell *current = dummy;
    if (current->next == dummy) {
        printf("Empty\n");
        return;
    } 
    while (current->next != dummy) {
        printf("%d ", current->next->value);
        current = current->next;
    }
    printf("\n");
    return;
}

// 全てのセルを削除する関数
void delete_all_cells(Cell *dummy) {
    while(dummy->next != dummy){
        Cell *tmp = dummy->next;
        dummy->next = tmp->next;
        if(tmp->next != NULL){
            tmp->next->prev = dummy;
        }
        free(tmp);
    }
}

void print_not_found(int num) {
    printf("Not Found %d\n", num);
}

void print_found(int num) {
    printf("Found %d\n", num);
}