#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a;  // ヒープ本体
    int num;  // ヒープに入っている要素の個数
} Heap;

void insert(Heap *heap, int val);
void upheap(Heap *heap, int x);
int delete_min(Heap *heap);
void downheap(Heap *heap);
void debug_print(Heap *heap);

int main(void){
    int n, i, tmp;
    Heap heap;
    
    scanf("%d", &n);
    if ((heap.a = (int *)malloc(n*sizeof(int))) == NULL) {
        printf("メモリが足りません\n");
        exit(1);
    }
    heap.num = 0;
    
    for(i=0; i<n; i++) {
        scanf("%d", &tmp);
        insert(&heap, tmp);  // 木に挿入
    }
    
    for(i=0; i<n; i++) {
        if(i>0) putchar(' ');
        tmp = delete_min(&heap);  // 木から取り出す
        printf("%d", tmp);
    }
    putchar('\n');
    free(heap.a);
    return 0;
}

/**
 * @brief ヒープに値valを挿入する関数 
 * @param heap ヒープの構造体のポインタ
 * @param val 挿入する値
 */
void insert(Heap *heap, int val) {
    heap->a[heap->num] = val;
    upheap(heap, heap->num);
    heap->num++;
}

/**
 * @brief 添字xのヒープの要素を必要な位置まで上げる関数
 * @param heap ヒープの構造体のポインタ
 * @param x 要素の添字
 */
void upheap(Heap *heap, int x){
    if(x < 1)return;
    while(x != 0){
        if(heap->a[x] < heap->a[(x-1)/2]){
            int tmp = heap->a[x];
            heap->a[x] = heap->a[(x-1)/2];
            heap->a[(x-1)/2] = tmp;
            x = (x-1)/2;
        }else{
            return;
        }
    }
}

/**
 * @brief ヒープの最小値を持つノードを削除し、最小値を返す関数 
 * @param heap ヒープの構造体のポインタ
 * @return ヒープの最小値を返す
 */
int delete_min(Heap *heap) {
    int tmp = heap->a[0];
    downheap(heap);
    return tmp;
}

/**
 * @brief ヒープの先頭の要素を必要な位置まで下ろす関数 
 * @param heap ヒープの構造体のポインタ
 */
void downheap(Heap *heap){
    int i = 0, tmp;
    heap->a[i] = heap->a[--heap->num];
    while(2*i+1 <= heap->num-1){
        if(heap->a[2*i+1] <= heap->a[2*i+2]){
            if(heap->a[i] > heap->a[2*i+1]){
                tmp = heap->a[i];
                heap->a[i] = heap->a[2*i+1];
                heap->a[2*i+1] = tmp;
                i = 2*i+1;
            }else{
                return;
            }
        }else{
            if(heap->a[i] > heap->a[2*i+2]){
                tmp = heap->a[i];
                heap->a[i] = heap->a[2*i+2];
                heap->a[2*i+2] = tmp;
                i = 2*i+2;
            }else{
                return;
            }
        }
    }
}

/**
 * @brief ヒープを出力するデバッグ用の関数
 * @param heap ヒープの構造体
 */
void debug_print(Heap *heap){
    int i;
    for(i=0; i<heap->num; i++) {
        if(i>0) fprintf(stderr, " ");
        fprintf(stderr, "%d", heap->a[i]);
    }
    fprintf(stderr, "\n");
}