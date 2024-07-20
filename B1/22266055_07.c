#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void reverse(char *str,int size){
	int i,j;
	char tmp;
	for(i=0,j=size-1;i<size/2;i++,j--){
		tmp=str[i];
		str[i]=str[j];
		str[j]=tmp;
	}
}

int main(){
	int n;
	char *str;
	while(scanf("%d", &n) != EOF){
		str = malloc(n*sizeof(int));
		if(scanf("%s", str) != EOF){
			reverse(str,n);	
			printf("%s\n", str);
		}
		free(str);
	}
	return 0;
}