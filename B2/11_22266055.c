#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
// #define ENABLE_UI // コメントアウトを外すとUIが表示されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#define UI_PRINT2(x, y) fprintf(stderr, x, y)
#else
#define UI_PRINT(x) do {} while (0)
#define UI_PRINT2(x, y) do {} while (0)
#endif

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    int age;  // 年齢
} Person;

typedef struct node_ {
    struct node_ *left; // 左の子へのポインタ
    struct node_ *right; // 右の子へのポインタ
    Person data;  // データ
} Node;

typedef enum{
    INSERT  = 0,
    SEARCH  = 1,
    DELETE  = 2,
} Mode;

int insert_node(Node **node, Person *person);
Node *search_node(Node *node, char name[]);
int delete_node(Node **node, char name[]);
void free_nodes(Node *node);
void print_all_nodes(Node *node);
void print_insertion_error(char name[], int age);
void print_not_found(char name[]);
void print_found(char name[]);
void visualize_tree(Node* node);

int main(void) {
    int i, num, mode, result;
    Person tmp;
    Node *searched_node, *root = NULL;

    UI_PRINT("操作回数を入力してください：\n");
    scanf("%d", &num);
  
    for (i = 0; i < num; i++) {
        // 入力
        UI_PRINT("[0 name age] 挿入, [1 name] 探索, [2 name] 削除：\n");
        scanf("%d",&mode);
        switch (mode) {
            case INSERT:
                scanf("%s %d", tmp.name, &tmp.age);
                break;
            case SEARCH:
            case DELETE:
                scanf("%s", tmp.name);
                break;
        }

        // 操作
        switch (mode) {
            case INSERT:
            result = insert_node(&root, &tmp);
            break;
            case SEARCH:
            searched_node = search_node(root, tmp.name);
            break;
            case DELETE:
            result = delete_node(&root, tmp.name);
            break;
        }
        
        // 出力
        switch (mode) {
            case INSERT:
            if (result == -1) {
				print_insertion_error(tmp.name, tmp.age);
            } else {
				print_all_nodes(root);
                printf("\n");
			}
            break;
            
            case SEARCH:
            if (searched_node == NULL) print_not_found(tmp.name);
            else print_found(tmp.name);	
            break;
            
            case DELETE:
            if (result == -1) { 
				print_not_found(tmp.name);
			} else {
				print_all_nodes(root);
				printf("\n");
			}
            break;
        } 
    }
    visualize_tree(root);
    free_nodes(root);
    return 0;
}

/**
 * @brief dataを書き込んだノードを作成する関数
 * @param node 根ノードへのポインタ
 * @param data 挿入するPerson型のデータ
 */ 
Node *make_node(Person *data){
    Node *node;
	if ((node=(Node*)malloc(sizeof(Node))) == NULL) {
        printf("メモリが足りません\n");
		exit(1);
	}
	node->data = *data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**
 * @brief ノードを挿入する関数
 * @param node 根ノードへのダブルポインタ
 * @param data 挿入するPerson型のデータ
 * @return 挿入に成功したら0、
 *         既に同じキー値を持つデータが存在し挿入に失敗したら-1を返す
 */
int insert_node(Node **node, Person *data){
	Node *root = *node, *parent = NULL;
    Node *newNode = make_node(data);
    while(root != NULL){
        parent = root;
        if(strcmp(root->data.name, data->name) == 0){
            return -1;
        }else if(strcmp(root->data.name, data->name) > 0){
            root = root->left;
        }else{
            root = root->right;
        }
    }
    if(parent == NULL){
        *node = newNode;
    }else if(strcmp(parent->data.name, data->name) > 0){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
    return 0;
}

/**
 * @brief ノードを探索する関数
 * @param node 根ノードへのポインタ
 * @param name 探索するname
 * @return 探索に成功したらノードのポインタ、
 *         データが存在せず探索に失敗したらNULLを返す
 */
Node *search_node(Node *node, char name[]){
	Node *root = node;
    while(root != NULL){
        if(root == NULL){
            return NULL;
        }
        if(strcmp(root->data.name, name) == 0){
            return root;
        }else if(strcmp(root->data.name, name) > 0){
            root = root->left;
        }else{
            root = root->right;
        }
    }
}

/**
 * @brief 最大の値を持つノードを削除し、最大の値を持つノードを指すポインタを返す関数
 * @param node 根ノードへのダブルポインタ
 * @note ヒントを記載しましたが別の方法で実装しても構いません
 * @return 最大の値を持つノードを指すポインタ
 */
Node *delete_maxnode(Node **node) {
	Node *p_max;  // 最大の値を持つノードを指すポインタ
    while((*node)->right != NULL){
        node = &(*node)->right;
    }
    p_max = *node;
    if((*node)->left != NULL){
        *node = (*node)->left;
    }else{
        *node = NULL;
    }
	return p_max;
}

/**
 * @brief ノードを削除する関数
 * @param node 根ノードへのダブルポインタ
 * @param name 削除するname
 * @note ヒントを記載しましたが別の方法で実装しても構いません
 * @return 削除に成功したら0、
 *         データが存在せず削除に失敗したら-1を返す
 */
int delete_node(Node **node, char name[]){
	int cmp;
    Node *p_max;
	while (*node != NULL){
		cmp = strcmp(name, (*node)->data.name);
        if (cmp == 0) {  // 削除（別途、メモリの解放も行うこと）
            if((*node)->left == NULL && (*node)->right == NULL){  // nodeが子を持たない
                free(*node);
                *node = NULL;
            }else if((*node)->left == NULL && (*node)->right != NULL){  // nodeが右の子のみ持つ
                Node *tmp = *node;
                *node = (*node)->right;
                free(tmp);
            }else if((*node)->left != NULL && (*node)->right == NULL){  // nodeが左の子のみ持つ
                Node *tmp = *node;
                *node = (*node)->left;
                free(tmp);
            }else{  // 左の子と右の子を持つ
                p_max = delete_maxnode(&(*node)->left);
                p_max->left = (*node)->left;
                p_max->right = (*node)->right;
                free(*node);
                *node = p_max;
            }
			return 0;  // 削除成功
		} else if (cmp < 0) {
            // 削除するノードはnodeよりも小さいので、左の子をたどる
			node = &(*node)->left;
		} else {
            // 削除するノードはnodeよりも大きいので、右の子をたどる
			node = &(*node)->right;
		}
	}
	return -1;  // 削除失敗
}

/**
 * @brief 全てのノードをfreeする関数
 * @param node 根ノードへのポインタ
 * @note 帰りがけ順に辿ると葉から順にfreeできます
 */
void free_nodes(Node *node) {
    if (node == NULL) return;
	free_nodes(node->left);
	free_nodes(node->right);
    free(node);
}

/**
 * @brief 全てのノードを昇順に出力する関数
 * @param node 根ノードへのポインタ
 * @note 通りがけ順に辿ると昇順に出力できます。
 */
void print_all_nodes(Node *node) {
    if (node == NULL) return;
	print_all_nodes(node->left);
	printf("%s %d, ", node->data.name, node->data.age);
	print_all_nodes(node->right);
}

void print_insertion_error(char name[], int age) {
    printf("Insertion Error: %s %d\n", name, age);
}

void print_not_found(char name[]) {
    printf("Not Found: %s\n", name);
}

void print_found(char name[]) {
    printf("Found: %s\n", name);
}

/**
 * @brief 木構造を見やすく出力する再帰関数
 * @param prefix プレフィックス
 * @param node 根ノードへのポインタ
 * @param is_left nodeが左の子ノードであるとき1、そうでないとき0
 * @note 参考：https://stackoverflow.com/a/51730733
 * @note 左の子が上側、右の子が下側に表示されます
 */
void visualize_recursion(char prefix[], Node* node, int is_left) {
    if(node != NULL) {
        UI_PRINT2("%s", prefix);
        UI_PRINT2("%s", is_left ? "├──" : "└──");

        // print the value of the node
        UI_PRINT2("%s\n", node->data.name);

        // enter the next tree level - left and right branch
        char new_prefix[1000];
        strcpy(new_prefix, prefix);
        strcat(new_prefix, (is_left ? "│   " : "    "));
        visualize_recursion(new_prefix, node->left, 1);
        visualize_recursion(new_prefix, node->right, 0);
    }
}

/**
 * @brief 木構造を見やすく出力する関数
 * @param node 根ノードへのポインタ
 */
void visualize_tree(Node* node) {
    visualize_recursion("", node, 0); 
}