#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 100 //キューの容量
#define QUANTUM 10 // CPU時間
// #define ENABLE_UI // コメントアウトを外すとUIが表示されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#else
#define UI_PRINT(x) do {} while (0)
#endif

typedef struct{
    int id;   // タスクID
	int time; // 処理時間
} Task;

typedef struct{
    Task *que; // キュー本体
    int front; // 先頭の添字
    int rear;  // 末尾の次の添字
    int num;   // 現在のデータ数
    int size;  // スタックの容量
} TaskQueue;

void error_overflow();
void error_underflow();
void initialize(TaskQueue *queue, int size);
void enqueue(TaskQueue *queue, Task data);
Task dequeue(TaskQueue *queue);
int is_empty(TaskQueue *queue);
int is_full(TaskQueue *queue);
void round_robin_scheduling(TaskQueue *queue);

int main(void){
	int i, num, task_id, task_time;
	TaskQueue queue;
	Task task;

	UI_PRINT("タスクの数を入力してください:\n");
	scanf("%d", &num);
	getchar();  // 改行文字の読み捨て

	initialize(&queue, QUEUE_SIZE); //キューの初期化

	UI_PRINT("[タスクID 処理時間]を入力してください:\n");
	for (i = 0; i < num; i++) {
		scanf("%d %d", &task_id, &task_time);
		task.id = task_id;
		task.time = task_time;
		enqueue(&queue, task);
	}
	round_robin_scheduling(&queue);
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
 * @param queue TaskQueue型のポインタ
 * @param size キューの容量
 */
void initialize(TaskQueue *queue, int size) {
	// TODO: ここにコードを書いてください
}

/**
 * @brief キューにenqueueする関数
 * @param queue TaskQueue型のポインタ
 * @param data enqueueするデータ
 * @note キューが満杯のときはエラー関数を呼び出してください
 */
void enqueue(TaskQueue *queue, Task data){
	// TODO: ここにコードを書いてください
}

/**
 * @brief キューからdequeueする関数
 * @param queue TaskQueue型のポインタ
 * @return dequeueしたデータ
 * @note キューが空のときはエラー関数を呼び出してください
 */
Task dequeue(TaskQueue *queue){
	// TODO: ここにコードを書いてください
}

/**
 * @brief キューが空かどうかを判定する関数
 * @param queue TaskQueue型のポインタ
 * @return 空なら1、空でなければ0
 */
int is_empty(TaskQueue *queue){
	// TODO: ここにコードを書いてください
}

/**
 * @brief キューが満杯かどうかを判定する関数
 * @param queue TaskQueue型のポインタ
 * @return 満杯なら1、満杯でなければ0
 */
int is_full(TaskQueue *queue){
	// TODO: ここにコードを書いてください
}

/**
 * @brief ラウンドロビン・スケジューリングを再現し、結果を出力する関数
 * @param queue TaskQueue型のポインタ
 */
void round_robin_scheduling(TaskQueue *queue){
	// TODO: ここにコードを書いてください
}