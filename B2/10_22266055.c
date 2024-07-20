#include <stdio.h>
#include <stdlib.h>

// #define ENABLE_UI // コメントアウトを外すとUIが表示されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#else
#define UI_PRINT(x) do {} while (0)
#endif

typedef struct node_ {
  struct node_ *left; // 左の子へのポインタ
  struct node_ *right; // 右の子へのポインタ
  int num;  // ノード番号
} Node;

typedef struct{
    int *que;
    int front;
    int rear;
    int num;
    int size;
}Queue;

Node* make_tree(int n_node, int node_num[], int left[], int right[], Node *node);
void initialize(Queue *queue, int size);
void enqueue(Queue *queue, int val);
int dequeue(Queue *queue);
void display_preorder(Node *node);
void display_inorder(Node *node);
void display_postorder(Node *node);
void display_breadth_first(Node *node, int size);

int main(void){
	int i, n_node;
	int *node_num, *left, *right;
	Node *node, *root;

	UI_PRINT("ノードの数を入力してください:\n");
	scanf("%d", &n_node);
	getchar();  // 改行文字の読み捨て

	node_num = (int *)malloc(n_node*sizeof(int));
	if (node_num == NULL) {printf("メモリが足りません\n"); exit(1);}
	left = (int *)malloc(n_node*sizeof(int));
	if (left == NULL) {printf("メモリが足りません\n"); exit(1);}
	right = (int *)malloc(n_node*sizeof(int));
	if (right == NULL) {printf("メモリが足りません\n"); exit(1);}
	node = (Node *)malloc(n_node*sizeof(Node));
	if (node == NULL) {printf("メモリが足りません\n"); exit(1);}

	for (i = 0; i < n_node; i++) {
		// ノード番号は0~n_node-1の整数で、子を持たない場合は-1を入力すること
		UI_PRINT("[ノード番号 左の子の番号 右の子の番号] を入力してください\n");
        scanf("%d %d %d", &node_num[i], &left[i], &right[i]);
	}
	root = make_tree(n_node, node_num, left, right, node);
	printf("Pre: ");
	display_preorder(root);
	printf("\nIn: ");
	display_inorder(root);
	printf("\nPost: ");
	display_postorder(root);
	printf("\nBreadth: ");
	display_breadth_first(root, n_node);
	printf("\n");
	free(node_num);
	free(left);
	free(right);
	free(node);
	return 0;
}

/**
 * @brief 木を作成して根を返す関数
 * @param n_node ノードの数
 * @param node_num ノード番号が入った配列
 * @param left 左の子のノード番号が入った配列
 * @param right 右の子のノード番号が入った配列
 * @return 作成した木の根
 */
Node* make_tree(int n_node, int node_num[], int left[], int right[], Node *node){
	int i, root_index;
	int *parent;  // parent[i]: ノード番号 num[i] の親（存在しないときは-1）

	if ((parent=(int*)malloc(n_node*sizeof(int))) == NULL) {
        printf("メモリが足りません\n"); exit(1);
	}
	for(i=0; i<n_node; i++) parent[i] = -1;  // 初期値として-1を代入
	
	// ノードに代入
	for(i=0; i<n_node; i++){
		node[node_num[i]].num = node_num[i];
		// 子が存在するときは子のノード番号、子が存在しないときはNULLを代入
		node[node_num[i]].left = (left[i] >= 0)? &node[left[i]] : NULL;
		node[node_num[i]].right = (right[i] >= 0)? &node[right[i]] : NULL;
		// 子が存在するときのみ、parent[子のノード番号]に親のノード番号を代入
		if (left[i] >= 0) parent[left[i]] = node_num[i];
		if (right[i] >= 0) parent[right[i]] = node_num[i];
	}
	
	// 根ノードの添字の取得
	for(i=0; i<n_node; i++) {
		// 親が存在しないのは根ノードのみ
		if (parent[i] == -1) {root_index = i; break;}
	}
	free(parent);
	
	return &node[root_index];
}

void initialize(Queue *queue, int size){
    queue->que = (int*)malloc(size*sizeof(int));
    queue->front = 0;
    queue->rear = 0;
    queue->num = 0;
    queue->size = size;
}

void enqueue(Queue *queue, int val){
    queue->que[queue->rear] = val;
    queue->rear = (queue->rear+1) % queue->size;
    queue->num++;
}

int dequeue(Queue *queue){
    int tmp = queue->que[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    queue->num--;
    return tmp;
}

/**
 * @brief node以下の部分木のノード番号を行きがけ順で表示する関数
 * @param node ノード
 * @note 最後の番号を出力した後は空白を入れた後、改行してください
 */
void display_preorder(Node *node){
	if(node == NULL)return;
	printf("%d ", node->num);
	display_preorder(node->left);
	display_preorder(node->right);
}

/**
 * @brief node以下の部分木のノード番号を通りがけ順で表示する関数
 * @param node ノード
 * @note 最後の番号を出力した後は空白を入れた後、改行してください
 */
void display_inorder(Node *node){
	if(node == NULL)return;
	display_inorder(node->left);
	printf("%d ", node->num);
	display_inorder(node->right);
}

/**
 * @brief node以下の部分木のノード番号を帰りがけ順で表示する関数
 * @param node ノード
 * @note 最後の番号を出力した後は空白を入れた後、改行してください
 */
void display_postorder(Node *node){
	if(node == NULL)return;
	display_postorder(node->left);
	display_postorder(node->right);
	printf("%d ", node->num);
}

/**
 * @brief node以下の部分木のノード番号を幅優先で表示する関数
 * @param node ノード
 * @note 最後の番号を出力した後は空白を入れた後、改行してください
 */
void display_breadth_first(Node *node, int size){
	Queue queue;
    initialize(&queue, size);
    enqueue(&queue, 0);
    while(queue.num > 0){
        int x = dequeue(&queue);
        printf("%d ", node[x].num);
        if(node[x].left != NULL){
            enqueue(&queue, node[x].left - node);
        }
        if(node[x].right != NULL){
            enqueue(&queue, node[x].right - node);
        }
    }
}