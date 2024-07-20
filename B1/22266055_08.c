#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
    int n,i;
    char **wordlist;
    char buf[31];
    wordlist=(char**)malloc(sizeof(char*)*1000);
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%s",buf);
        wordlist[i]=(char*)malloc(strlen(buf)+1);
        strcpy(wordlist[i],buf);
    }
    for(i=0;i<n;i++){
        printf("%s\n",wordlist[n-i-1]);
    }
    for(i=0;i<=n;i++){
        free(wordlist[i]);
    }
    free(wordlist);
    
    return 0;
}