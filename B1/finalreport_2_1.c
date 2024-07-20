#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TREENODE{
  int data;
  struct TREENODE *p_left;
  struct TREENODE *p_right;
}TreeNode;

TreeNode *CreateNewNode() {
  TreeNode *p_new_node = (TreeNode*)malloc(sizeof(TreeNode));
  p_new_node -> data=0;
  p_new_node -> p_left = p_new_node -> p_right = NULL;
  return p_new_node;
}

TreeNode * makeTree(FILE *fp,TreeNode *tp){
    TreeNode *Node= (TreeNode*)malloc(sizeof(TreeNode));
    Node=tp;
    fp=fopen("morsecode.txt","r");
    if(fp==NULL)puts("ファイルはない");
    int s;
    while((s = fgetc(fp)) != EOF){
        while(s=='.' || s=='-'){
            if(Node==NULL)Node=CreateNewNode();
            if(s=='.'){
                if(Node->p_left==NULL)Node->p_left=CreateNewNode();
                Node=Node->p_left;
                break;
            }else if(s=='-'){
                if(Node->p_right==NULL)Node->p_right=CreateNewNode();
                Node=Node->p_right;
                break;
        }
        }
        if(s>='a' && s<='z'){
            if(Node==NULL)Node=CreateNewNode();
            Node->data=s;
            Node=tp;
    }
    }
    fclose(fp);
    return tp;
}

void scanprintmoji(TreeNode *tp){
    TreeNode *Node=tp;
    char s;
    int k;
    k=scanf("%c",&s);
    while(k!=EOF){
        while(s!=' ' && s!='\n'){
            if(s=='/')printf(" ");
            if(s=='\n')printf("\n");
            else if(s=='.'){
                Node=Node->p_left;
            }else if(s=='-'){
                Node=Node->p_right;
            }
        scanf("%c",&s);
        }
        printf("%c",Node->data);
        if(s=='\n')printf("\n");
        Node=tp;
        k=scanf("%c",&s);
    }
}
void DeleteTree(TreeNode *pNode) {
  if(pNode -> p_left  != NULL) DeleteTree(pNode -> p_left);
  if(pNode -> p_right != NULL) DeleteTree(pNode -> p_right);
  free(pNode);
}
int main(void) {
  TreeNode *root_node = CreateNewNode(); 
  FILE *fp;
  root_node=makeTree(fp,root_node);
  scanprintmoji(root_node);
  DeleteTree(root_node);
  return 0;
}