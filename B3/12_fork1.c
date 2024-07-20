#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int val = 1;
    switch(fork()) { /* 子プロセス生成 */
    case 0: /* 子プロセス */
        val += 2;
        printf("子プロセス:%d\n", val);
        exit(0) ;
    case -1: /* fork()のエラー */
        perror("child process") ;
        break;
    default: /* 親プロセス */
        val += 3;
        printf("親プロセス:%d\n", val);
        wait(&val) ; 
    }
}