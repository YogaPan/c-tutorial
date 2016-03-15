#include <stdio.h>

#define add(x, y) ((x) + (y))

#define swap(x, y) do { \
	x ^= y;         \
	y ^= x;         \
	x ^= y;         \
} while (0)

int main(void)
{
	int answer;
	int x;
	int y;

	x = 3;
	y = 4;
	printf("x=%d y=%d\n", x, y);
	swap(x, y);
	printf("x=%d y=%d\n", x, y);

	answer = add(x, y);
	printf("x+y=%d\n", answer);

	return 0;
}
