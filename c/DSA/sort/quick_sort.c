#include <stdio.h>

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

static void quick_sort(int *array, int left, int right)
{
	int i = left;
	int j = right + 1;

	if (left < right) {
		for (;;) {
			while (i + 1 < ARRAY_SIZE && array[++i] < array[left]);
			while (j - 1 > -1 && array[--j] > array[left]);
			if (i >= j)
				break;
			else
				swap(array[i], array[j]);
		}
		swap(array[left], array[j]);
		quick_sort(array, left, j-1);
		quick_sort(array, j+1, right);
	}
}

int main(void)
{
	int i;
	int array[ARRAY_SIZE] = { 1, 51, 23, 33, 55, 5, 91, 43, 7, 11 };
	FILE *fp;

	fp = fopen(RANDOM_FILE, "r");

	for (i = 0; i < ARRAY_SIZE; i++)
		fscanf(fp, "%d", &array[i]);

	quick_sort(array, 0, ARRAY_SIZE-1);
	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	fclose(fp);

	return 0;
}
