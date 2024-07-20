#include <stdio.h>
#include <stdlib.h>

#define FAIL_RETURN(flg,message) if(flg){printf("%s",message);freeList();exit(1);}

typedef struct LISTNODE {
	int data;
	struct LISTNODE *pNext;
	struct LISTNODE *pPrev;
} ListNode;

ListNode rootNode;

int addNode(int num, int val) {
	ListNode *pPrevNode = &rootNode;
	ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->data = val;

	for(int Pos=1; Pos<num; Pos++)
		pPrevNode = pPrevNode -> pNext;

	pNewNode->pNext = pPrevNode->pNext;
	pPrevNode->pNext = pNewNode;

    pNewNode->pPrev = pPrevNode;
    (pNewNode->pNext)->pPrev = pNewNode;

	return 0;
}

int deleteNode(int num) {
	ListNode *pPrevNode = &rootNode,*tmpNode1,*tmpNode2;
	for(int Pos=1; Pos<num; Pos++)
		pPrevNode = pPrevNode->pNext;

	if(pPrevNode->pNext!=NULL){
		tmpNode1 = pPrevNode->pNext;
		pPrevNode->pNext = (pPrevNode->pNext)->pNext;
        tmpNode2 = (pPrevNode->pNext)->pPrev;
        (pPrevNode->pNext)->pPrev = pPrevNode;
	}
	return 0;
}

int swapNode(int num1, int num2) {
	int Pos;
	ListNode *pPrevNode1 = &rootNode,*tmpNode1_1,*tmpNode1_2;
	ListNode *pPrevNode2 = &rootNode,*tmpNode2_1,*tmpNode2_2;
	for(Pos=1; Pos<num1; Pos++)
		pPrevNode1 = pPrevNode1->pNext;
	for(Pos=1; Pos<num2; Pos++)
		pPrevNode2 = pPrevNode2->pNext;

	if(pPrevNode1->pNext != NULL && pPrevNode2->pNext != NULL){
		if(abs(num1-num2) != 1){
			tmpNode1_1 = (pPrevNode1->pNext)->pNext;
			tmpNode1_2 = pPrevNode1->pNext;
			(pPrevNode1->pNext)->pNext = (pPrevNode2->pNext)->pNext;
			(pPrevNode2->pNext)->pNext = tmpNode1_1;
			pPrevNode1->pNext = pPrevNode2->pNext;
			pPrevNode2->pNext = tmpNode1_2;

			tmpNode2_1 = (((pPrevNode1->pNext)->pNext)->pPrev)->pPrev;
			tmpNode2_2 = ((pPrevNode1->pNext)->pNext)->pPrev;
			(((pPrevNode1->pNext)->pNext)->pPrev)->pPrev = (((pPrevNode2->pNext)->pNext)->pPrev)->pPrev;
			(((pPrevNode2->pNext)->pNext)->pPrev)->pPrev = tmpNode2_1;
			((pPrevNode1->pNext)->pNext)->pPrev = ((pPrevNode2->pNext)->pNext)->pPrev;
			((pPrevNode2->pNext)->pNext)->pPrev = tmpNode2_2;
		}
		else if(num2-num1 == 1){
			tmpNode1_1 = (pPrevNode2->pNext)->pNext;
			tmpNode1_2 = pPrevNode2->pNext;
			(pPrevNode2->pNext)->pNext = pPrevNode1->pNext;
			pPrevNode2->pNext = tmpNode1_1;
			pPrevNode1->pNext = tmpNode1_2;

			tmpNode2_1 = pPrevNode2->pPrev;
			tmpNode2_2 = (pPrevNode1->pNext)->pPrev;
			pPrevNode2->pPrev = (pPrevNode2->pNext)->pPrev;
			(pPrevNode1->pNext)->pPrev = tmpNode2_1;
			(pPrevNode2->pNext)->pPrev = tmpNode2_2;
		}
		else if(num1-num2 == 1){
			tmpNode1_1 = (pPrevNode1->pNext)->pNext;
			tmpNode1_2 = pPrevNode1->pNext;
			(pPrevNode1->pNext)->pNext = pPrevNode2->pNext;
			pPrevNode1->pNext = tmpNode1_1;
			pPrevNode2->pNext = tmpNode1_2;

			tmpNode2_1 = pPrevNode1->pPrev;
			tmpNode2_2 = (pPrevNode2->pNext)->pPrev;
			pPrevNode1->pPrev = (pPrevNode1->pNext)->pPrev;
			(pPrevNode2->pNext)->pPrev = tmpNode2_1;
			(pPrevNode1->pNext)->pPrev = tmpNode2_2;
		}
	}
	return 0;
}

void showList(void) {
	ListNode *pPrevNode = &rootNode;
	while(pPrevNode->pNext != &rootNode){
		pPrevNode = pPrevNode->pNext;
		printf("%d ",pPrevNode->data);
	}
	printf("\n");
}

void reverseShowList(void) {
	ListNode *pPrevNode = &rootNode;
	while(pPrevNode -> pPrev != &rootNode){
		pPrevNode = pPrevNode -> pPrev;
		printf("%d ",pPrevNode -> data);
	}
	printf("\n");
}

void listSort(void) {
    int nodeNum;
    ListNode *pCheckNode, *pNextNode, *pEndNode;
    pEndNode = &rootNode;
    while(rootNode.pNext != pEndNode){
        pCheckNode = rootNode.pNext;
        nodeNum=0;
        while(pCheckNode->pNext != pEndNode){
            pNextNode = pCheckNode->pNext;
            nodeNum++;
            if(pCheckNode->data > pNextNode->data)swapNode(nodeNum,nodeNum+1);
            else pCheckNode = pCheckNode->pNext;
        }
        pEndNode = pEndNode->pPrev;
    }
}

void freeList(void) {
	ListNode *currentNode = rootNode.pNext;
	ListNode *tmp;
	
	for (;currentNode != &rootNode;) {
		tmp = currentNode;
		currentNode = currentNode -> pNext;
		free(tmp);
	}
}


int main(void) {
	int op, num1, num2, val;
	char message[256];
	
	rootNode.data = 0;
	rootNode.pNext = rootNode.pPrev = &rootNode;
	
	while (scanf("%d", &op), op) {
		switch (op) {
			case 1:
				showList();
				break;
			case 2:
				reverseShowList();
				break;
			case 3:
				scanf("%d%d", &num1, &val);
				sprintf(message, "error in addNode(%d, %d)\n", num1, val);
				FAIL_RETURN(addNode(num1, val), message)
				break;
			case 4:
				scanf("%d", &num1);
				sprintf(message, "error in deleteNode(%d)\n", num1);
				FAIL_RETURN(deleteNode(num1), message)
				break;
			case 5:
				scanf("%d%d", &num1, &num2);
				sprintf(message, "error in swapNode(%d, %d)\n", num1, num2);
				FAIL_RETURN(swapNode(num1, num2), message)
				break;
			case 6:
				listSort();
				break;			}
	}
	
	freeList();
	
	return 0;
}