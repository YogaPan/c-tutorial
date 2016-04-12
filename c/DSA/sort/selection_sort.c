#include <stdio.h>

#define ARRAY_SIZE 10

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
	int array[ARRAY_SIZE] = { 32, 11, 99, 51, 32, 0, 54, 9, 3, 11 };

	selection_sort(array, ARRAY_SIZE);
	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
}
