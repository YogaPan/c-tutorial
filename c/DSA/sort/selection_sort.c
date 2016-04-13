#include <stdio.h>

#define swap(x, y) \
({ \
	typeof(x) __tmp = x; \
	x = y; \
	y = __tmp; \
})

void selection_sort(int *array, int size)
{
	int i, j;
	int min;

	for (i = 0; i < size; i++) {
		min = i;

		for (j = i + 1; j < size; j++) {
			if (array[j] < array[min])
				min = j;
		}
		if (min != i)
			swap(array[min], array[i]);
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

	selection_sort(array, ARRAY_SIZE);
	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	fclose(fp);

	return 0;
}
