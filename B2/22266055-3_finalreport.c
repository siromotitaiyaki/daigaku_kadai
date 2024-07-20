#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define HASH 100
#define N 1

typedef struct cell_ {
    struct cell_ *next;
    int num;
} Cell;

void initialize_hash_table(Cell *table[]){
    int i;
    for(i=0; i<HASH; i++){
        table[i] = NULL;
    }
}

void print_all_buckets(Cell *table[]){
    int i;
    int num = 0;
    for(i=0; i<HASH; i++){
        Cell *p = table[i];
        while(p != NULL){
            num++;
            printf("%d ", p->num);
            p = p->next;
        }
    }
    if(num == 0){
        printf("Empty\n");
    }else{
        printf("\n");
    }
}

int main(void){
    int n, x, i, cell, hash, flag = 0;
    clock_t start, end;
    srand((unsigned int)time(NULL));
    scanf("%d", &n);
    Cell *table[HASH];
    initialize_hash_table(table);

    table[1] = (Cell*)malloc(sizeof(Cell));
    table[1]->num = 1;
    table[1]->next = NULL;

    for(i=1, cell=1; i<n; i++){
        cell = cell + (rand() % N) + 1;
        hash = cell % HASH;
        Cell *root = table[hash];
        if(table[hash] == NULL){
            table[hash] = (Cell*)malloc(sizeof(Cell));
            table[hash]->num = cell;
            table[hash]->next = NULL;
        }else{
            while(root->next != NULL){
                if(root->num == cell){
                    break;
                }
                root = root->next;
            }
            root->next = (Cell*)malloc(sizeof(Cell));
            root->next->num = table[hash]->num;
            root->next->next = NULL;
            table[hash]->num = cell;
        }
    }
    print_all_buckets(table);

    scanf("%d", &x);

    start = clock();

    hash = x % HASH;
    if(table[hash] == NULL){
        printf("Not Found:%d\n", x);
    }else if(table[hash]->num == x){
        printf("Found:%d\n", x);
    }else{
        Cell *cell = table[hash];
        while(cell != NULL){
            if(cell->num == x){
                printf("Found:%d\n", x);
                flag = 1;
                break;
            }
            cell = cell->next;
        }
        if(flag == 0){
            printf("Not Found:%d\n", x);
        }
    }

    end = clock();

    printf("clock:%f\n", (double)(end-start) / CLOCKS_PER_SEC);

    for(i = 0; i < HASH; i++){
        Cell *p = table[i];
        while(p != NULL){
            Cell *tmp = p;
            p = p->next;
            free(tmp);
        }
    }

    return 0;
}