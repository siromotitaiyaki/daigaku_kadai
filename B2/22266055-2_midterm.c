#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int *que;
    int front;
    int rear;
    int num;
    int size;
}Queue;

void error_wall();
void error_underflow();
void initialize(Queue *queue, int size);
void enqueue(Queue *queue, int val);
int dequeue(Queue *queue);

int main(void){
    int H,W,Sx,Sy,Gx,Gy;
    int i,j,k,l,n;
    int way;
    scanf("%d %d",&H,&W);
    scanf("%d %d",&Sx,&Sy);
    scanf("%d %d",&Gx,&Gy);
    char maze[H][W][2];
    int size = H*W;
    int count[size];
    int num[size];
    for(i=0; i<H; i++){
        for(j=0; j<W; j++){
            scanf("%s",maze[i][j]);
        }
    }
    for(int a=0; a<size; a++){
        count[a] = 0;
        num[a] = 0;
    }

    if(strcmp(maze[Sx][Sy], "#") == 0 || strcmp(maze[Gx][Gy], "#") == 0){
        error_wall();
    }

    Queue *queue;
    initialize(queue, size);

    int Start = (Sx*W)+Sy, Goal = (Gx*W)+Gy;
    if(Start == Goal){
        printf("0\n");
        return 0;
    }
    enqueue(queue, Start);
    count[Start] = 1;
    num[0]++;
    for(k=Start, l=1; k!=Goal; l++){
        for(n=0; n<num[l-1]; n++){
            k = dequeue(queue);
            int x=k/W, y=k%W;
            if(x!=0 && y!=0){
                if(strcmp(maze[x-1][y-1],".") == 0 && count[k-W-1] == 0){
                    if(k-W-1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k-W-1] = 1;
                    enqueue(queue, k-W-1);
                    num[l]++;
                }
            }
            if(x!=0){
                if(strcmp(maze[x-1][y],  ".") == 0 && count[k-W] == 0){
                    if(k-W == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k-W] = 1;
                    enqueue(queue, k-W);
                    num[l]++;
                }
            }
            if(x!=0 && y!=W){
                if(strcmp(maze[x-1][y+1],".") == 0 && count[k-W+1] == 0){
                    if(k-W+1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k-W+1] = 1;
                    enqueue(queue, k-W+1);
                    num[l]++;
                }
            }
            if(y!=0){
                if(strcmp(maze[x][y-1],  ".") == 0 && count[k-1] == 0){
                    if(k-1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k-1] = 1;
                    enqueue(queue, k-1);
                    num[l]++;
                }
            }
            if(y!=W){
                if(strcmp(maze[x][y+1],  ".") == 0 && count[k+1] == 0){
                    if(k+1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k+1] = 1;
                    enqueue(queue, k+1);
                    num[l]++;
                }
            }
            if(x!=H && y!=0){
                if(strcmp(maze[x+1][y-1],".") == 0 && count[k+W-1] == 0){
                    if(k+W-1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k+W-1] = 1;
                    enqueue(queue, k+W-1);
                    num[l]++;
                }
            }
            if(x!=H){
                if(strcmp(maze[x+1][y],  ".") == 0 && count[k+W] == 0){
                    if(k+W == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k+W] = 1;
                    enqueue(queue, k+W);
                    num[l]++;
                }
            }
            if(x!=H && y!=W){
                if(strcmp(maze[x+1][y+1],".") == 0 && count[k+W+1] == 0){
                    if(k+W+1 == Goal){
                        way = l;
                        printf("%d\n",way);
                        return 0;
                    }
                    count[k+W+1] = 1;
                    enqueue(queue, k+W+1);
                    num[l]++;
                }
            }
        }
    }
}

void error_wall(){
    printf("ERROR: スタートかゴールが壁になっています。\n");
    exit(0);
}

void error_underflow(){
	printf("ERROR: ゴールに辿りつけませんでした。\n");
	exit(0);  
}

void initialize(Queue *queue, int size){
    int array[size];
    queue->que = array;
    queue->front = 0;
    queue->rear = 0;
    queue->num = 0;
    queue->size = size;
    for(int i=0; i<size; i++){
        queue->que[i] = 0;
    }
}

void enqueue(Queue *queue, int val){
    queue->que[queue->rear] = val;
    queue->rear++;
    queue->num++;
}

int dequeue(Queue *queue){
    if(queue->num <= 0){
        error_underflow();
    }
    int tmp = queue->que[queue->front];
    queue->front++;
    queue->num--;
    return tmp;
}