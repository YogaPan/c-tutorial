#include <stdio.h>

#define PRINT_VAR(var)                 \
	printf("%s=%d\n", #var, var)

#define UNDERLINE_VAR(var)             \
	int _##var

int main(void)
{
	UNDERLINE_VAR(a);

	_a = 3;
	PRINT_VAR(_a);

	return 0;
}
