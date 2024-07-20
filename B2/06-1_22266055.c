#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 100 //キューの容量
// #define ENABLE_UI // コメントアウトを外すとUIが表示されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#else
#define UI_PRINT(x) do {} while (0)
#endif

typedef enum{
	ENQUEUE  = 0,
	DEQUEUE  = 1,
	SHOW     = 2,
	IS_FULL  = 3,
	IS_EMPTY = 4,
} Mode;

typedef struct{
    int *que;  // キュー本体
    int front; // 先頭の添字
    int rear;  // 末尾の次の添字
    int num;   // 現在のデータ数
    int size;  // スタックの容量
} IntQueue;


void error_overflow();
void error_underflow();
void initialize(IntQueue *queue, int size);
void enqueue(IntQueue *queue, int val);
int dequeue(IntQueue *queue);
void show(IntQueue *queue);
int is_empty(IntQueue *queue);
int is_full(IntQueue *queue);

int main(void){
	int i, num, val, mode;
	IntQueue queue;

	UI_PRINT("操作回数を入力してください:\n");
	scanf("%d", &num);
	getchar();  // 改行文字の読み捨て

	initialize(&queue, QUEUE_SIZE); //キューの初期化

	for (i = 0; i < num; i++) {
        UI_PRINT("[0 val] enqueue, [1] dequeue, "
		"[2] Show, [3] Full?, [4] Empty?:\n");
		scanf("%d",&mode);
		switch ((Mode)mode) {
			case ENQUEUE:
				scanf("%d", &val);
				enqueue(&queue, val);
				break;
			case DEQUEUE:
				printf("%d\n", dequeue(&queue));
				break;
			case SHOW:
				show(&queue);
				break;
			case IS_FULL:
				printf("%s\n", is_full(&queue)? "Yes" : "No");
				break;
			case IS_EMPTY:
				printf("%s\n", is_empty(&queue)? "Yes" : "No");
				break;	
		}
	}
	free(queue.que);
	return 0;
}

/**
 * @brief オーバーフロー時のエラー関数	
 */
void error_overflow(){
	printf("ERROR: Queue Over Flow\n");
	// 本来、異常終了exit(1)としたいが、採点の都合のためexit(0)
	exit(0);  
}

/**
 * @brief アンダーフロー時のエラー関数
 */
void error_underflow(){
	printf("ERROR: Queue Under Flow\n");
	// 本来、異常終了exit(1)としたいが、採点の都合のためexit(0)
	exit(0);  
}

/**
 * @brief キューを初期化する関数
 * @param queue IntQueue型のポインタ
 * @param size キューの容量
 */
void initialize(IntQueue *queue, int size) {
	queue->que = malloc(sizeof(int)*size);
    queue->front = 0;
    queue->rear = 0;
    queue->num = 0;
    queue->size = size;
}

/**
 * @brief キューにenqueueする関数
 * @param queue IntQueue型のポインタ
 * @param val enqueueする値
 * @note キューが満杯のときはエラー関数を呼び出してください
 */
void enqueue(IntQueue *queue, int val){
	if(queue->num >= queue->size){
		error_overflow();
	}else{
		queue->que[queue->rear] = val;
        queue->rear = (queue->rear+1) % queue->size;
        queue->num++;
	}
}

/**
 * @brief キューからdequeueする関数
 * @param queue IntQueue型のポインタ
 * @return dequeueしたデータ
 * @note キューが空のときはエラー関数を呼び出してください
 */
int dequeue(IntQueue *queue){
	if(queue->num <= 0){
		error_underflow();
	}else{
        int tmp = queue->que[queue->front];
        queue->front = (queue->front+1) % queue->size;
        queue->num--;
        return tmp;
	}
}

/**
 * @brief 空白区切りでキューの中身を表示する関数
 * @param queue IntQueue型のポインタ
 * @note 最後の要素の後ろには空白を表示せず、改行してください
 */
void show(IntQueue *queue){
	if(queue->num <= 0){
		return;
	}else{
		int tmp=queue->front;
		for(int i=0; i<queue->num; i++,tmp++){
			if(tmp>=queue->size){
				tmp=0;
			}
			printf("%d ",queue->que[tmp]);
		}
		printf("\n");
	}
}

/**
 * @brief キューが空かどうかを判定する関数
 * @param queue IntQueue型のポインタ
 * @return 空なら1、空でなければ0
 */
int is_empty(IntQueue *queue){
	if(queue->num == 0){
		return 1;
	}else{
		return 0;
	}
}

/**
 * @brief キューが満杯かどうかを判定する関数
 * @param queue IntQueue型のポインタ
 * @return 満杯なら1、満杯でなければ0
 */
int is_full(IntQueue *queue){
	if(queue->num >= queue->size){
		return 1;
	}else{
		return 0;
	}
}