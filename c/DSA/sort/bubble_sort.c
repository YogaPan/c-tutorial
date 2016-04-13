#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

static void bubble_sort(int *array, int size)
{
	int i, j;
	int flags = TRUE;

	for (i = 0; i < size - 1 && flags; i++) {
		for (j = 0; j < size - i - 1; j++) {
			flags = FALSE;
			if (array[j] > array[j+1]) {
				swap(array[j], array[j+1]);
				flags = TRUE;
			}
		}
	}
}

int main(void)
{
	int i;
	int array[ARRAY_SIZE];
	FILE *fp;

	fp = fopen(RANDOM_FILE, "r");

	for (i = 0; i < ARRAY_SIZE; i++)
		fscanf(fp, "%d", &array[i]);

	bubble_sort(array, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	fclose(fp);

	return 0;
}
