#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int i, v;
    for(i = 0; i < 8; ++i){
        v = rand();
        write(1, &v, sizeof(v));
    }
}