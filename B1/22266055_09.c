#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define LENGTH 30

int main(void){

	int i,j,n;
	char **wordlist;
    char tmp[LENGTH+1];
	char in_name[LENGTH+1],out_name[LENGTH+1];
	
	scanf("%s %s",in_name,out_name);
	FILE *fp_input = fopen(in_name, "r");
	FILE *fp_output = fopen(out_name, "w");

    fscanf(fp_input,"%d",&n);
    wordlist=malloc(n*sizeof(int*));
    for(i=0;i<n;i++){
        wordlist[i]=malloc((LENGTH+1)*sizeof(int*));
        fscanf(fp_input,"%s",wordlist[i]);
    }

    for(i=0;i<n;i++){
        for(j=1;j<n-i;j++){
            if(strcmp(wordlist[i],wordlist[i+j])>0){
                strcpy(tmp,wordlist[i]);
                strcpy(wordlist[i],wordlist[i+j]);
                strcpy(wordlist[i+j],tmp);
            }
        }
    }
        
    for(i=0;i<n;i++){
        fprintf(fp_output,"%s\n",wordlist[i]);
    }
    
    for(i=0;i<n;i++){
        free(wordlist[i]);
    }free(wordlist);

	fclose(fp_input);
	fclose(fp_output);

	return 0;
}