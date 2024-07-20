#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE  1024
#define ARGVSIZE 100

const char whitespace[] = " \t\r\n\v";

int parsecmd(char **argv, char *buf, char *ebuf)
{
	char *s;
	int  i = 0;
	
	s = buf;

	while (s < ebuf) {
		while (s < ebuf && strchr(whitespace, *s)) s++;
		if (ebuf <= s) return -1;

		argv[i++] = s;
		while (s < ebuf && !strchr(whitespace, *s)) s++;
		*s = '\0'; 
		s++;
	}

	return 1;
}

#include <fcntl.h> // ファイル操作

void runcmd(char *buf)
{
	char *argv[ARGVSIZE];
	int fd; // ファイルディスクリプタ
	
	memset(argv, 0, sizeof(char*)*ARGVSIZE);
	if (parsecmd(argv, buf, &buf[strlen(buf)]) > 0) {
		// ">"の処理
		char *output_file = NULL;
		for (int i = 0; argv[i] != NULL; i++) {
			if (strcmp(argv[i], ">") == 0 && argv[i+1] != NULL) { // ">"発見
				output_file = argv[i+1];
				argv[i] = NULL; // ">"を引数から削除
				break;
			}
		}
		
		if (output_file != NULL) { // ">"発見時の処理
			fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // ファイルを開く
			dup2(fd, STDOUT_FILENO); // リダイレクト
			close(fd);
		}

		if (execvp(argv[0], argv) < 0)
			perror("execvp");		
	}
	exit(-1);
}

int getcmd(char *buf, int len)
{
	printf("> ");
	fflush(stdin);
	memset(buf, 0, len);
	fgets(buf, len, stdin);

	if (buf[0] == 0)
		return -1;
	return 0;
}

int main(int argc, char**argv)
{
	static char buf[BUFSIZE];

	while(getcmd(buf, BUFSIZE) >= 0) {
		if (fork() == 0)
			runcmd(buf);
		wait(NULL);
	}

	exit(0);
}