#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>

static inline void show_inode(struct stat *s)
{
	printf("%lld ", s->st_ino);
}

static void show_user(struct stat *s)
{
	struct passwd *user;

	user = getpwuid(s->st_uid);
	printf("%s ", user->pw_name);
}

static void show_permission(struct stat *s)
{
	if (S_IRUSR & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWUSR & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IXUSR & s->st_mode)
		printf("x");
	else
		printf("-");

	if (S_IRGRP & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWGRP & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IXGRP & s->st_mode)
		printf("x");
	else
		printf("-");

	if (S_IROTH & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWOTH & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IROTH & s->st_mode)
		printf("x");
	else
		printf("-");
}

static int show_stat(const char *path)
{
	int ret;
	struct stat s;

	if (access(path, F_OK) < 0) {
		fprintf(stderr, "path not exists\n");
		return -1;
	}

	ret = stat(path, &s);
	if (ret < 0) {
		perror("stat");
		return -1;
	}

	show_inode(&s);
	show_user(&s);
	show_permission(&s);
	printf("\n\n");

	return 0;
}

int main(int argc, const char *argv[])
{
	const char *path = argv[1];

	show_stat(path);

	return 0;
}
