#include <stdio.h>

int main(void)
{
	printf("file: %s\n", __FILE__);
	printf("line: %d\n", __LINE__);
	printf("function: %s\n", __func__);
	printf("date: %s\n", __DATE__);

	return 0;
}
