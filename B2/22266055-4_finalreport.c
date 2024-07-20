#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define HASH 100
#define N 3

typedef struct cell_ {
    int num;
} Cell;

void initialize_hash_table(Cell table[]){
    int i;
    for(i=0; i<HASH; i++){
        table[i].num = -1;
    }
}

void print_all_buckets(Cell table[]){
    int i;
    int num = 0;
    for(i=0; i<HASH; i++){
        if(table[i].num != -1){
            num++;
            printf("%d ", table[i].num);
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
    Cell table[HASH];
    initialize_hash_table(table);

    table[1].num = 1;

    for(i=1, cell=1; i<n; i++){
        cell = cell + (rand() % N) + 1;
        hash = cell % HASH;
        while(table[hash].num != -1){
            hash = (hash + 1) % HASH;
        }
        table[hash].num = cell;
    }
    print_all_buckets(table);

    scanf("%d", &x);

    start = clock();

    hash = x % HASH;
    while(table[hash].num != -1){
        if(table[hash].num == x){
            printf("Found:%d\n", x);
            flag = 1;
            break;
        }
        hash = (hash + 1) % HASH;
    }
    if(flag == 0){
        printf("Not Found:%d\n", x);
    }

    end = clock();

    printf("clock:%f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}