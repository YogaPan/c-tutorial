#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, const char **argv)
{
	DIR *dir;
	struct dirent *entry;
	const char *filename;

	if (argc != 2) {
		fprintf(stderr, "usage: dir dirname\n");
		exit(1);
	}
	filename = argv[1];

	if ((dir = opendir(filename)) == NULL) {
		perror("opendir");
		exit(1);
	}
	while ((entry = readdir(dir)) != NULL)
		printf("%s\n", entry->d_name);
	closedir(dir);

	return 0;
}
