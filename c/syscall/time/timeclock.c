#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	struct timespec start, end;
	int sec;

	clock_gettime(CLOCK_REALTIME, &start);
	sleep(2);
	clock_gettime(CLOCK_REALTIME, &end);

	sec = end.tv_sec - start.tv_sec;
	printf("%d\n", sec);

	return 0;
}
