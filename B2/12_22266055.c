#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define BUCKET_SIZE 100

// #define ENABLE_UI // コメントアウトを外すとUIが表示されます
// #define ENABLE_VISUALIZE  // コメントアウトを外すと操作終了後のバケットの様子が出力されます

#ifdef ENABLE_UI
#define UI_PRINT(x) fprintf(stderr, x)
#else
#define UI_PRINT(x) do {} while (0)
#endif

#ifdef ENABLE_VISUALIZE
#define VISUALIZE 1
#else
#define VISUALIZE 0
#endif

typedef enum {
    INSERT = 0,
    SEARCH = 1,
    DELETE = 2,
} Mode;

typedef struct {
    char name[MAX_NAME_LENGTH];  // 名前
    int age;                     // 年齢
} Person;

typedef struct cell_ {
    struct cell_ *next;  // 次のセルへのポインタ
    Person person;       // 値
} Cell;

int hash_string(char *str);
int insert_bucket(Cell *table[], Person *person);
Cell *search_bucket(Cell *table[], char name[]);
int delete_bucket(Cell *table[], char name[]);
void initialize_hash_table(Cell *table[]);
Cell *make_bucket(Person *data);
void print_all_buckets(Cell *table[]);
void delete_all_buckets(Cell *table[]);
void visualize_all_buckets(Cell *table[]);
void print_insertion_error(char name[], int age);
void print_not_found(char name[]);
void print_found(char name[]);

int main(void) {
    int i, num, mode, result;
    Person tmp;
    Cell *table[BUCKET_SIZE], *searched_bucket;

    initialize_hash_table(table);

    UI_PRINT("操作回数を入力してください：\n");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        // 入力
        UI_PRINT("[0 name age] 挿入, [1 name] 探索, [2 name] 削除：\n");
        scanf("%d", &mode);
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
                result = insert_bucket(table, &tmp);
                break;
            case SEARCH:
                searched_bucket = search_bucket(table, tmp.name);
                break;
            case DELETE:
                result = delete_bucket(table, tmp.name);
                break;
        }

        // 出力
        switch (mode) {
            case INSERT:
                if (result == -1)
                    print_insertion_error(tmp.name, tmp.age);
                else
                    print_all_buckets(table);
                break;

            case SEARCH:
                if (searched_bucket == NULL)
                    print_not_found(tmp.name);
                else
                    print_found(tmp.name);
                break;

            case DELETE:
                if (result == -1)
                    print_not_found(tmp.name);
                else
                    print_all_buckets(table);
                break;
        }
    }
    if (VISUALIZE) {
        visualize_all_buckets(table);
    }
    delete_all_buckets(table);
    return 0;
}

/**
 * @brief 文字列をキー値とするハッシュ関数
 * @param *str 文字列の先頭のポインタ
 * @return ハッシュ値
 * @note 文字コードの加算を行い、
 *       BUCKET_SIZEで割った余りをハッシュ値としてください
 */
int hash_string(char *str) {
    int i, sum=0;
    for(i=0; i<strlen(str); i++){
        sum += str[i];
    }
    return sum % BUCKET_SIZE;
}

/**
 * @brief バケットを挿入する関数
 * @param table ハッシュ表
 * @param person 挿入するPerson型のデータ
 * @return 挿入に成功したら0、
 *         既に同じキー値を持つデータが存在し挿入に失敗したら-1を返す
 */
int insert_bucket(Cell *table[], Person *person) {
    int hash = hash_string(person->name);
    Cell *cell = make_bucket(person);
    Cell *root = table[hash];
    if(table[hash] == NULL){
        table[hash] = cell;
    }else{
        while(root != NULL){
            if(strcmp(root->person.name, person->name) == 0){
                return -1;
            }
            root = root->next;
        }
        Cell *tmp = table[hash];
        table[hash] = cell;
        table[hash]->next = tmp;
    }
    return 0;
}

/**
 * @brief バケットを探索する関数
 * @param table ハッシュ表
 * @param name 探索するname
 * @return 探索に成功したらバケットのポインタ、
 *         データが存在せず探索に失敗したらNULLを返す
 */
Cell *search_bucket(Cell *table[], char name[]) {
    int hash = hash_string(name);
    Cell *cell = table[hash];
    if(table[hash] == NULL){
        return NULL;
    }
    if(strcmp(table[hash]->person.name, name) == 0){
        return table[hash];
    }
    while(cell != NULL){
        if(strcmp(cell->person.name, name) == 0){
            return cell;
        }
        cell = cell->next;
    }
    return NULL;
}

/**
 * @brief バケットを削除する関数
 * @param table ハッシュ表
 * @param name 削除するname
 * @return 削除に成功したら0、
 *         データが存在せず削除に失敗したら-1を返す
 */
int delete_bucket(Cell *table[], char name[]) {
    int hash = hash_string(name);
    Cell *cell = table[hash];
    Cell *root = table[hash];
    if(table[hash] == NULL){
        return -1;
    }
    if(strcmp(cell->person.name, name) == 0){
        Cell *tmp = cell;
        table[hash] = cell->next;
        free(tmp);
        return 0;
    }
    while(cell->next != NULL){
        cell = cell->next;
        if(strcmp(cell->person.name, name) == 0){
            Cell *tmp = cell;
            root->next = cell->next;
            free(tmp);
            return 0;
        }
        root = root->next;
    }
    return -1;
}

/**
 * @brief ハッシュ表を初期化する関数
 * @param table ハッシュ表
 */
void initialize_hash_table(Cell *table[]) {
    int i;
    for (i = 0; i < BUCKET_SIZE; i++) {
        table[i] = NULL;
    }
}

/**
 * @brief バケットを作成して返す関数
 * @param data 作成するバケットの持つPerson型のデータ
 * @return 作成したセル
 */
Cell *make_bucket(Person *data) {
    Cell *cell = (Cell *)malloc(sizeof(Cell));
    if (cell == NULL) {
        printf("メモリが足りません");
        exit(1);
    }
    cell->person = *data;
    cell->next = NULL;
    return cell;
}

/**
 * @brief 全てのバケットを出力する関数
 * @param table ハッシュ表
 */
void print_all_buckets(Cell *table[]) {
    int i;
	int num = 0; // バケット数
    for (i = 0; i < BUCKET_SIZE; i++) {
        Cell *p = table[i];
        while (p != NULL) {
			num++;
            printf("%s %d, ", p->person.name, p->person.age);
            p = p->next;
        }
    }
	if (num == 0) {  // バケットが存在しないときは"Empty"を出力
        printf("Empty\n");
	} else {
        printf("\n");
	}
}

/**
 * @brief 全てのバケットを削除する関数
 * @param table ハッシュ表
 */
void delete_all_buckets(Cell *table[]) {
    int i;
	Cell *p_delete;
    for (i = 0; i < BUCKET_SIZE; i++) {
		while (table[i] != NULL) {
			p_delete = table[i];
            table[i] = table[i]->next;
			free(p_delete);
        }
    }
}

/**
 * @brief 全てのバケットを可視化する関数
 * @param table ハッシュ表
 * @note 標準エラー出力なので提出時に残っていても大丈夫です
 */
void visualize_all_buckets(Cell *table[]) {
    int i;
    for (i = 0; i < BUCKET_SIZE; i++) {
        Cell *p = table[i];
        fprintf(stderr, "[%02d] ", i);
        while (p != NULL) {
            fprintf(stderr, "-> [%s %d] ", p->person.name, p->person.age);
            p = p->next;
        }
        fprintf(stderr, "\n");
    }
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
