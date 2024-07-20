#include<stdio.h>
#include<stdlib.h>

typedef struct LISTNODE{
    int data;
    struct LISTNODE *next;
} ListNode;

ListNode *getNewNode(int val, ListNode *next){
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = val;
    node->next = next;
    return node;
}

ListNode *getUnion(ListNode *a, ListNode *b){
    int tmp;
    ListNode *union_set = getNewNode(0,NULL);
    ListNode *pos = union_set;
    a = a->next;
    b = b->next;
    while(a || b){
        if(a && b){
            if(a->data < b->data){
                tmp = a->data;
                a = a->next;
            }else if(a->data > b->data){
                tmp = b->data;
                b = b->next;
            }else{
                tmp = a->data;
                a = a->next;
                b = b->next;
            }
        }else if(a){
            tmp = a->data;
            a = a->next;
        }else{
            tmp = b->data;
            b = b->next;
        }
        ListNode *new = getNewNode(tmp,NULL);
        pos->next = new;
        pos = pos->next;
        union_set->data++;
    }
    return union_set;
}

ListNode *getIntersect(ListNode *a, ListNode *b){
    int tmp;
    ListNode *itsct_set = getNewNode(0,NULL);
    ListNode *pos = itsct_set;
    a = a->next;
    b = b->next;
    while(a && b){
        if(a->data < b->data){
            a = a->next;
        }else if(a->data > b->data){
            b = b->next;
        }else{
            ListNode *new = getNewNode(a->data,NULL);
            pos->next = new;
            pos = pos->next;
            itsct_set->data++;
            a = a->next;
            b = b->next;
        }
    }
    return itsct_set;
}

void insert(ListNode *head, int val){
    ListNode *tail = head;
    for(; tail->next; tail = tail->next){
        if(tail->data == val && head != tail){
            return;
        }
        if(tail->next->data > val){
            tail->next = getNewNode(val, tail->next);
            head->data++;
            return;
        }
    }
    if(tail->data != val){
        tail->next = getNewNode(val,NULL);
        head->data++;
    }
}

void printList(ListNode *head){
    ListNode *pos = head->next;
    printf("{");
    while(pos){
        printf("%d",pos->data);
        pos = pos->next;
        if(pos){
            printf(", ");
        }
    }
    printf("}\n");
}

void deleteList(ListNode *head){
    if(head->next){
        deleteList(head->next);
    }
    free(head);
}

int main(void)
{
    int num,i;
    int val;
    ListNode *a = getNewNode(0,NULL);
    ListNode *b = getNewNode(0,NULL);
    ListNode *union_set, *itsct_set;
    printf("A:");
    scanf("%d:",&num);
    printf("%d:",num);
    for(i=0; i<num; i++){
        scanf("%d",&val);
        insert(a,val);
    }
    printf("B:");
    scanf("%d:",&num);
    printf("%d:",num);
    for(i=0; i<num; i++){
        scanf("%d",&val);
        insert(b,val);
    }
    union_set = getUnion(a,b);
    itsct_set = getIntersect(a,b);
    printf("A = ");
    printList(a);
    printf("B = ");
    printList(b);
    printf("(Union of A and B) = ");
    printList(union_set);
    printf("(Intersection of A and B) = ");
    printList(itsct_set);
    deleteList(a);
    deleteList(b);
    deleteList(union_set);
    deleteList(itsct_set);
    return 0;
}