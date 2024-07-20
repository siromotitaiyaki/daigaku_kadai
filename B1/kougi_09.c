#include <stdio.h>
#include <stdlib.h>
/*--- src からの入力をタブを展開して dst へ出力 ---*/
void detab(FILE *src, FILE *dst, int width){
int ch, pos = 1;
while ((ch=fgetc(src)) != EOF) {
int num;
switch (ch) {
case '\t': /* タブ文字 */

num = width - (pos - 1) % width;
for ( ; num > 0; num--) {
fputc(' ', dst);
pos++;
}
break;
case '\n': /* 改行文字 */

fputc(ch, dst); pos=1; break;

default: /* それ以外の文字 */

fputc(ch, dst); pos++; break;

}
}
}
int main(int argc, char *argv[]){
int width = 8;
FILE *fp;
if (argc < 2)
detab(stdin, stdout, width); /* 標準入力 → 標準出力 */
else {

while (--argc > 0) {
if (**(++argv) == '-') {
if (*++(*argv) == 't')
width = atoi(++*argv);
else {
fputs("パラメータが不正です。\n", stderr);
return (1);
}

} else if ((fp = fopen(*argv, "r")) == NULL) {
fprintf(stderr, "ファイル%s が正しくオープンできません。\n", *argv);
return (1);
} else {
detab(fp, stdout, width); /* ストリーム fp → 標準出力 */
fclose(fp);
}
}
}
return (0);
}