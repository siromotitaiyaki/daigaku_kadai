#include <stdio.h>
#include <stdlib.h>

#define FAIL_RETURN(flg,message) if(flg){printf("%s",message);freeList();exit(1);}

typedef struct LISTNODE {
	int data;
	struct LISTNODE *pNext;
} ListNode;

ListNode rootNode;

int addNode(int num, int val) {
	int Pos;
	ListNode *pPrevNode = &rootNode;
	ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->data = val;

	for(Pos=1; Pos<num; Pos++)
		pPrevNode = pPrevNode -> pNext;

	pNewNode->pNext = pPrevNode->pNext;
	pPrevNode->pNext = pNewNode;
	return 0;
}

int deleteNode(int num) {
	int Pos;
	ListNode *pPrevNode = &rootNode,*tmpNode;
	for(Pos=1; Pos<num; Pos++)
		pPrevNode = pPrevNode -> pNext;

	if(pPrevNode->pNext!=NULL){
		tmpNode = pPrevNode -> pNext;
		pPrevNode->pNext = (pPrevNode->pNext)->pNext;
		free(tmpNode);
	}
	return 0;
}

void showList(void) {
	ListNode *pPrevNode=&rootNode;
	while(pPrevNode->pNext!=NULL){
		pPrevNode=pPrevNode->pNext;
		printf("%d ",pPrevNode->data);
	}
	printf("\n");
}

void freeList(void) {
	ListNode *currentNode = rootNode.pNext;
	ListNode *tmp;
	
	for (;currentNode != NULL;) {
		tmp = currentNode;
		currentNode = currentNode -> pNext;
		free(tmp);
	}
}


int main(void) {
	int op, num, val;
	char message[256];
	
	rootNode.data = 0;
	rootNode.pNext = NULL;
	
	while (scanf("%d", &op), op) {
		switch (op) {
			case 1:
				showList();
				break;
			case 2:
				scanf("%d %d", &num, &val);
				sprintf(message, "error in addNode(%d, %d)\n", num, val);
				FAIL_RETURN(addNode(num, val), message)
				break;
			case 3:
				scanf("%d", &num);
				sprintf(message, "error in deleteNode(%d)\n", num);
				FAIL_RETURN(deleteNode(num), message)
				break;
		}
	}
	
	freeList();
	
	return 0;
}