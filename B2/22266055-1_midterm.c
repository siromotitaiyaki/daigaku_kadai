#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

typedef enum{
	PUSH     = 0,
	POP      = 1,
	SHOW     = 2,
	IS_FULL  = 3,
	IS_EMPTY = 4,
}Mode;

typedef struct cell_{
    struct cell_ *next;
    int val;
}Cell;

Cell *make_cell(int num);
void error_overflow();
void error_underflow();
void initialize(Cell *stack);
void push(Cell *stack, int val);
int pop(Cell *stack);
void show(Cell *stack);
int is_empty(Cell *stack);
int is_full(Cell *stack);

int main(void){
    int i,num,val,mode;
    Cell *dummy;
    Cell *stack;
    unsigned int sec;
    int nsec;
    double d_sec;
    
    struct timespec start_time, end_time;

    dummy = make_cell(0);
    dummy->next = NULL;
    stack = dummy;

    fprintf(stderr,"操作回数を入力してください。\n");
    scanf("%d",&num);
    getchar();

    clock_gettime(NULL, &start_time);

    initialize(dummy);

    for(i=0; i<num; i++){
        fprintf(stderr,"[0 val] Push, [1] Pop, [2] Show, [3] Full?, [4] Empty?:\n");
		scanf("%d",&mode);
		switch((Mode)mode){
			case PUSH:
				scanf("%d",&val);
				push(dummy,val);
				break;
			case POP:
				printf("%d\n",pop(dummy));
				break;
			case SHOW:
				show(dummy);
				break;
			case IS_FULL:
				printf("%s\n",is_full(dummy)? "Yes" : "No");
				break;
			case IS_EMPTY:
				printf("%s\n",is_empty(dummy)? "Yes" : "No");
				break;	
		}
	}

    clock_gettime(NULL, &end_time);
sec = end_time.tv_sec - start_time.tv_sec;
    nsec = end_time.tv_nsec - start_time.tv_nsec;

    d_sec = (double)sec
        + (double)nsec / (1000 * 1000 * 1000);

    /* 計測時間の表示 */
    printf(
        "time:%f\n", d_sec
    );
    free(stack);
    return 0;
}

Cell *make_cell(int num){
    Cell *cell = (Cell*)malloc(sizeof(Cell));
    if(cell == NULL){
        printf("メモリが足りません");
        exit(1);
    }
    cell->val = num;
    cell->next = NULL;
    return cell;
}

void error_underflow(){
	printf("ERROR: Stack Under Flow\n");
	exit(0);  
}

void initialize(Cell *stack){
    stack->next = 0;
    stack->val = 0;
}

void push(Cell *stack, int val){
    Cell *cell = make_cell(val);
    while(stack->next != NULL){
        stack = stack->next;
    }
    cell->next = stack->next;
    stack->next = cell;
}

int pop(Cell *stack){
    if(stack == NULL || stack->next == NULL){
        error_underflow();
    }else{
        Cell *cell = stack->next;
        while(cell->next != NULL){
            cell = cell->next;
            stack = stack->next;
        }
        int val = cell->val;
        stack->next = NULL;
        return val;
    }
}

void show(Cell *stack){
    if(stack == NULL || stack->next == NULL){
        return;
    }else{
        Cell *cell = stack->next;
        while(cell != NULL){
            printf("%d ",cell->val);
            cell = cell->next;
        }
        printf("\n");
    }
}

int is_empty(Cell *stack){
    if(stack == NULL || stack->next == NULL){
        return 1;
    }else{
        return 0;
    }
}

int is_full(Cell *stack){
    return 0;
}