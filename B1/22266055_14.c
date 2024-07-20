#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TREENODE{
    char *data;
    struct TREENODE *p_left;
    struct TREENODE *p_right;
}TreeNode;

TreeNode *CreateNewNode(char *p_word) {
    TreeNode *p_new_node = (TreeNode*)malloc(sizeof(TreeNode));
    p_new_node -> data = (char*)malloc(sizeof(char)*strlen(p_word)+1);
    strcpy(p_new_node -> data,p_word);
    p_new_node -> p_left = p_new_node -> p_right = NULL;
    return p_new_node;
}

void PrintTree(TreeNode *pNode) {
    if(pNode -> p_left  != NULL) PrintTree(pNode -> p_left);
    printf("%s\n", pNode -> data);
    if(pNode -> p_right != NULL) PrintTree(pNode -> p_right);
}

TreeNode *AddNode(TreeNode *p_parent_node, char *p_word) {
    if(p_parent_node==NULL){
        return CreateNewNode(p_word);
    }else if(strcmp(p_parent_node->data,p_word)>0){
        if(p_parent_node->p_left==NULL){
            p_parent_node->p_left=AddNode(p_parent_node->p_left,p_word);
        }else{
            AddNode(p_parent_node->p_left,p_word);
        }
    
    }else{
        if(p_parent_node->p_right==NULL){
            p_parent_node->p_right=AddNode(p_parent_node->p_right,p_word);
        }else{
            AddNode(p_parent_node->p_right,p_word);
        }
    }
}

void DeleteTree(TreeNode *pNode) {
    if(pNode -> p_left  != NULL) DeleteTree(pNode -> p_left);
    if(pNode -> p_right != NULL) DeleteTree(pNode -> p_right);
    free(pNode -> data);
    free(pNode);
}

int main(void) {
        
    char word[31];

    if (scanf("%s", word) != EOF) {
        TreeNode *root_node = CreateNewNode(word);
        PrintTree(root_node);
        while (scanf("%s", word) != EOF) {
        AddNode(root_node, word);
        printf("\n");
        PrintTree(root_node);
        }
        DeleteTree(root_node);
    }

    return 0;
}