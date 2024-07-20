#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

int getunion(int a, int b){
    ListNode *pPrevNode = &rootNode;
    for(int i=1;i<a;i++){
        pPrevNode = pPrevNode->pNext;
        if(pPrevNode->data == b)return 0;
    }
    return 1;
}

long int bit(long int A){
    long int Abit=0;
    long int base = 1;

    while(A>0){
    Abit = Abit+(A%2)*base;
    A = A/2;
    base = base*10;
    }
    return Abit;
}

int Node(int Anum){
    int i,j,k;
    int A10;
    long int A2;
    int num[31];
    char text[31];
    for(A10=pow(2,Anum)-1; A10>0; A10--){
        A2=A10;
        sprintf(text,"%030ld",bit(A2));
        for(j=0;j<30;j++){
            num[j]=text[j]-'0';
        }
        for(i=30;i>Anum;i--){
            for(j=0;j<i;j++){
                num[j]=num[j+1];
            }
        }
        ListNode *pPrevNode = &rootNode;
        for(k=0;num[k]!=1;k++){
            pPrevNode = pPrevNode->pNext;
        }
        pPrevNode = pPrevNode->pNext;
        printf("{%d",pPrevNode->data);
        while(k+1<Anum){
            pPrevNode = pPrevNode->pNext;
            if(num[k+1]!=0){
                printf(", %d",pPrevNode->data);
            }k++;
        }
        printf("}\n");
    }
    return 0;
}

int main(void){
    int A,num;
    rootNode.data = 0;
	rootNode.pNext = NULL;
    ListNode *pPrevNode = &rootNode;
    printf("A:");
    scanf("%d",&A);
    if(A==0){
        printf("{}\n");
    }else{
        printf("%d:",A);
        for(int i=0;i<A;i++){
            scanf("%d",&num);
            if(getunion(i+1,num) == 1){
                addNode(i+1,num);
            }else{
                i--;A--;
            }
        }
        Node(A);
        printf("{}\n");
    }

    return 0;
}