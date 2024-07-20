#include <stdio.h>
#include <stdlib.h>

void hash(int a)
{
	int calc = 0;

	calc += a;
	calc += (calc << 10);
	calc ^= (calc >> 6);

	calc += calc<<3;
	calc ^= calc<<11;
	calc += calc<<15;

	printf("%d\n", calc);
}

void usage(char *cmd)
{
	fprintf(stderr, "Usage: %s num\n", cmd);
	exit(0);
}

int main(int argc, char **argv)
{
	int a;

	if (argc != 2) usage(argv[0]);
	
	a = atoi(argv[1]);
	hash(a);
	
	return 0;
}
	