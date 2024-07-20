#include<stdio.h>
void swap(int *piData1,int *piData2);

int main(){
    int iA=100;
    int iB=200;

    printf("iA:%d\n",iA);
    printf("iB:%d\n",iB);

    swap(&iA,&iB);

    printf("iA:%d\n",iA);
    printf("iB:%d\n",iB);
    return 0;
}

void swap(int *piData1,int *piData2){
    int i;
    i=*piData1; *piData1=*piData2; *piData2=i;
}