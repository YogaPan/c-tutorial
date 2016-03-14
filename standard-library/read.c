#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

void read(FILE *f);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: read filename\n");
		exit(1);
	}

	FILE *f;
	const char *filename;

	filename = argv[1];
	f = fopen(filename, "r");
	if (f)
		read(f);
	else
		fprintf(stderr, "ERROR\n");
	return 0;
}

void read(FILE *f)
{
	char buf[SIZE];

	while (fgets(buf, SIZE, f))
		printf("%s", buf);
}
