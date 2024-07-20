#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int c, val;
    int pfd[2];
    char *eargv[argc], buf[1024];
    FILE *fp;

    for(int i=1; i<argc; i++){
        eargv[i-1] = argv[i];
    }
    eargv[argc-1] = NULL;
    pipe(pfd); /* パイプを作成して */
    switch (fork()) { /* 子プロセスを生成する */
    case 0: // 子プロセス
        close(pfd[1]);
        read_data(pfd[0]);
        exit(0);
    case -1:
        perror("child process");
        break;
    default: // 親プロセス
        close(1);
        close(pfd[0]);
        dup(pfd[1]);
        if((fp = popen(eargv[0], "r"))==NULL){
            perror("popen");
            break;
        }
        while(fscanf(fp, "%s", &buf)!=EOF){
            write(1, buf, sizeof(buf));
        }
    }
}
read_data(int fd)
{
    int i, v;
    for(i = 0; i < 8; ++i) {
        read(fd, &v, sizeof(v));
        printf("read val:%d\n", v);
    }
}