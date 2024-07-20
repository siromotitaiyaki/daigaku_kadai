#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int val;
    char *eargv[argc];
    for(int i=1; i<argc; i++){
        eargv[i-1] = argv[i];
    }
    eargv[argc-1] = NULL;
    switch (fork()) {
    case 0: /* 子プロセス */
        execv(argv[0], eargv); /* ファイルの実行 */
        perror("can not exec");
        exit(0);
    case -1:
        perror("child process");
        break;
    default:
        /* ここは子プロセスと並行実行される */
        wait(&val); /* 親プロセスは終了を待つ */
    }
}