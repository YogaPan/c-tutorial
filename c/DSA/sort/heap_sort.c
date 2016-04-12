#include <stdio.h>

#define swap(x, y) \
({ \
	typeof(x) __tmp = x; \
	x = y; \
	y = __tmp; \
})

#define ARRAY_SIZE 10

void heapify(int *array, int size, int i)
{
	int root  = i;
	int left  = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && array[left] > array[root])
		root = left;
	if (right < size && array[right] > array[root])
		root = right;

	if (root != i) {
		swap(array[i], array[root]);
		heapify(array, size, root);
	}
}

void heap_sort(int *array, int size)
{
	int i;

	for (i = size / 2 - 1; i >= 0; i--)
		heapify(array, size, i);

	for (i = size - 1; i >= 0; i--) {
		swap(array[0], array[i]);
		heapify(array, i, 0);
	}
}

int main(void)
{
	int i;
	int array[ARRAY_SIZE] = { 12, 42, 90, 77, 51, 11, 60, 52, 42, 28 };

	heap_sort(array, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
}
