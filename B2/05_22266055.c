#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define STACK_SIZE 100 //スタックの容量

typedef enum{
	PUSH     = 0,
	POP      = 1,
	SHOW     = 2,
	IS_FULL  = 3,
	IS_EMPTY = 4,
} Mode;

typedef struct{
    int *stk; // スタック本体
	int ptr;  // スタックポインタ
	int size; // スタックの容量
} IntStack;

void error_overflow();
void error_underflow();
void initialize(IntStack *stack, int size);
void push(IntStack *stack, int val);
int pop(IntStack *stack);
void show(IntStack *stack);
int is_empty(IntStack *stack);
int is_full(IntStack *stack);
int rpn_calculator(IntStack *stack);

int main(void){
	int i, num, val, mode;
	IntStack stack;
	unsigned int sec;
    int nsec;
    double d_sec;
    
    struct timespec start_time, end_time;

	fprintf(stderr, "操作回数を入力してください。\n"
	"0を入力すると逆ポーランド電卓モードになります:\n");
	scanf("%d", &num);
	getchar();  // 改行文字の読み捨て

	clock_gettime(NULL, &start_time);

	initialize(&stack, STACK_SIZE); //スタックの初期化

	for (i = 0; i < num; i++) {
        fprintf(stderr, "[0 val] Push, [1] Pop, "
		"[2] Show, [3] Full?, [4] Empty?:\n");
		scanf("%d",&mode);
		switch ((Mode)mode) {
			case PUSH:
				scanf("%d", &val);
				push(&stack, val);
				break;
			case POP:
				printf("%d\n", pop(&stack));
				break;
			case SHOW:
				show(&stack);
				break;
			case IS_FULL:
				printf("%s\n", is_full(&stack)? "Yes" : "No");
				break;
			case IS_EMPTY:
				printf("%s\n", is_empty(&stack)? "Yes" : "No");
				break;	
		}
	}

	clock_gettime(NULL, &end_time);


	if (num <= 0) {
		fprintf(stderr, "逆ポーランド電卓モードです。式を入力してください:\n");
        printf("%d\n",rpn_calculator(&stack));
	}

	sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;

    d_sec = (double)sec
        + (double)nsec / (1000 * 1000 * 1000);

    /* 計測時間の表示 */
    printf(
        "time:%f\n", d_sec
    );

	return 0;
}

/**
 * @brief オーバーフロー時のエラー関数	
 */
void error_overflow(){
	printf("ERROR: Stack Over Flow\n");
	// 本来、異常終了exit(1)としたいが、採点の都合のためexit(0)
	exit(0);  
}
/**
 * @brief アンダーフロー時のエラー関数
 */
void error_underflow(){
	printf("ERROR: Stack Under Flow\n");
	// 本来、異常終了exit(1)としたいが、採点の都合のためexit(0)
	exit(0);  
}
/**
 * @brief スタックを初期化する関数
 * @param stack IntStack型のポインタ
 * @param size スタックの容量
 */
void initialize(IntStack *stack, int size) {
    int array[STACK_SIZE];
	stack->stk = array;
	stack->ptr = 0;
	stack->size = STACK_SIZE;
	for(int i=0;i<STACK_SIZE;i++){
		stack->stk[i] = 0;
	}
}

/**
 * @brief スタックにpushする関数
 * @param stack IntStack型のポインタ
 * @param val pushする値
 * @note スタックが満杯のときはエラー関数を呼び出してください
 */
void push(IntStack *stack, int val){
	if(stack->ptr >= STACK_SIZE){
		error_overflow();
	}else{
		stack->stk[stack->ptr] = val;
		stack->ptr++;
	}
}

/**
 * @brief スタックからpopする関数
 * @param stack IntStack型のポインタ
 * @return popしたデータ
 * @note スタックが空のときはエラー関数を呼び出してください
 */
int pop(IntStack *stack){
	if(stack->ptr <= 0){
		error_underflow();
	}else{
		stack->ptr--;
		int tmp=stack->stk[stack->ptr];
		stack->stk[stack->ptr] = 0;
		return(tmp);
	}
}

/**
 * @brief 空白区切りでスタックの中身を表示する関数
 * @param stack IntStack型のポインタ
 * @note 最後の要素の後ろには空白を表示せず、改行してください
 */
void show(IntStack *stack){
	if(stack->stk[0] == 0 || stack->stk[stack->ptr-1] == 0){
		return;
	}else{
		int i;
		for(i=0;i<stack->ptr-1;i++){
			printf("%d ",stack->stk[i]);
		}
		printf("%d\n",stack->stk[i++]);
	}
}

/**
 * @brief スタックが空かどうかを判定する関数
 * @param stack IntStack型のポインタ
 * @return 空なら1、空でなければ0
 */
int is_empty(IntStack *stack){
    if(stack->stk[0] == 0 || stack->stk[stack->ptr-1] == 0){
		return 1;
	}else{
		return 0;
	}
}

/**
 * @brief スタックが満杯かどうかを判定する関数
 * @param stack IntStack型のポインタ
 * @return 満杯なら1、満杯でなければ0
 */
int is_full(IntStack *stack){
    if(stack->stk[STACK_SIZE-1] == 0){
		return 1;
	}else{
		return 0;
	}
}

/**
 * @brief 逆ポーランド記法電卓を実現する関数
 * @param stack IntStack型のポインタ
 * @return 計算結果
 */
int rpn_calculator(IntStack *stack){
    char i,a,b;
	int c;
	for(;;){
		scanf("%c",&i);
		if('0'<i && i<='9'){
			push(stack, i);
		}else{
			switch(i){
				case '+':
					b=pop(stack);
					b=b-'0';
					a=pop(stack);
					a=a-'0';
					c=a+b;
					c=c+'0';
					push(stack, c);
					break;
				case '-':
					b=pop(stack);
					b=b-'0';
					a=pop(stack);
					a=a-'0';
					c=a-b;
					c=c+'0';
					push(stack, c);
					break;
				case '*':
					b=pop(stack);
					b=b-'0';
					a=pop(stack);
					a=a-'0';
					c=a*b;
					c=c+'0';
					push(stack, c);
					break;
				case '/':
					b=pop(stack);
					b=b-'0';
					a=pop(stack);
					a=a-'0';
					c=a/b;
					c=c+'0';
					push(stack, c);
					break;
				case '\n':
					a=pop(stack);
					a=a-'0';
					return a;
			}
		}
	}
}
