#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct LISTNODE{
	int no;
	struct LISTNODE *pNext;
}ListNode;

ListNode *rootNode;

int addNode(int num, int val) {
	int Pos;
	ListNode *pPrevNode = rootNode;
    ListNode *pNewNode;
    pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->no = val;
	for(Pos=1; Pos<num-1; Pos++)
		pPrevNode = pPrevNode->pNext;
	pPrevNode->pNext = pNewNode;
    pNewNode->pNext = rootNode;
	return 0;
}

ListNode *getNode(int num){
    int Pos;
	ListNode *retNode = rootNode;
	for(Pos=1; Pos<num; Pos++)
		retNode = retNode -> pNext;
    return retNode;
}

int deleteNode(ListNode *pPrevNode){
    ListNode *tmpNode;
	if(pPrevNode->pNext != NULL){
		tmpNode = pPrevNode->pNext;
        printf("%d\n",tmpNode->no);
		pPrevNode->pNext = (pPrevNode->pNext)->pNext;
		free(tmpNode);
	}
	return 0;
}

void Action(int N){
    ListNode *pPrevNode;
    int K,m,i;
    printf("K:");
    scanf("%d",&K);
    while(K >= N){
        printf("(K<N) K:");
        scanf("%d",&K);
    }
    printf("m:");
	scanf("%d",&m);
    while(m <= 1 || m >= N){
        printf("(1<m<N) m:");
        scanf("%d",&m);
    }
    printf("Out:\n");
    for(pPrevNode=getNode(K);pPrevNode->pNext!=pPrevNode;pPrevNode=pPrevNode->pNext){
        for(i=1; i<m-1; i++)
            pPrevNode = pPrevNode->pNext;
        deleteNode(pPrevNode);
    }
    printf("Win\n");
    printf("%d\n",pPrevNode->no);
    free(pPrevNode);
}

int main(void){
    int i,N;
    rootNode = (ListNode*)malloc(sizeof(ListNode));
    rootNode->no = 1;
	rootNode->pNext = rootNode;
    printf("N:");
    scanf("%d",&N);
    clock_t start,end;
    start=clock();
    for(i=1; i<N; i++){
        addNode(i+1,i+1);
    }
    Action(N);
    end=clock();
    printf("\ntime:%f\n",(double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}