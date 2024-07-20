#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int val;
    int pfd[2]; /* パイプのファイル記述子が格納 */
    pipe(pfd); /* パイプのファイル記述子を得る */
    switch (fork()) {
    case 0:
        /* 親プロセスへデータを書き出す */
        write_data(pfd[1]);
        exit(0);
    case -1:
        perror("child process");
        break;
    default:
        /* 子プロセスからデータを読み込む */
        read_data(pfd[0]);
        wait(&val);
    }
}
#define COUNT 128
write_data(int fd) /* fdは乱数データを書く */
{
    int i, v[COUNT];
    clock_t start_clock, end_clock;
    double clock_time;
    for(i = 0; i < COUNT; ++i) {
        v[i] = rand(); /* 乱数生成 */
    }
    start_clock = clock(); // 計測開始
    for(i = 0; i < COUNT; ++i) {
        write(fd, &v, sizeof(v));
    }
    end_clock = clock(); // 計測終了
    clock_time = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    printf("write:%f[byte/sec]\n", (double)(COUNT*4) / clock_time);
}
/* fdからデータを読んで端末へ書く */
read_data(int fd)
{
    int i, v;
    clock_t start_clock, end_clock;
    double clock_time;
    start_clock = clock(); // 計測開始
    for(i = 0; i < COUNT; ++i) {
        read(fd, &v, sizeof(v));
    }
    end_clock = clock(); // 計測終了
    clock_time = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    printf("read :%f[byte/sec]\n", (double)(COUNT*4) / clock_time);
}