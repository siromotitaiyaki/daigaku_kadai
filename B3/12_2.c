#include <stdio.h>
#include <stdlib.h>

void process() {
    static int staticval = 10; // 静的領域
    int *heapval = (int *)malloc(sizeof(int)); // ヒープ領域
    int stackval = 20; // スタック領域

    printf("機械語領域  : %p\n", (void *)process);
    printf("静的領域    : %p\n", (void *)&staticval);
    printf("ヒープ領域  : %p\n", (void *)heapval);
    printf("スタック領域: %p\n", (void *)&stackval);
}

void kakikomi() {
    char *kikaigo = (char *)kakikomi;
    *kikaigo = 'A'; // 
}

int main() {
    process();
    kakikomi();
    return 0;
}