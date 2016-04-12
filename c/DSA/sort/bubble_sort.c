#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define ARRAY_SIZE 10

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

static void bubble_sort(int *arr, int size)
{
	int i, j;
	int flags = TRUE;

	for (i = 0; i < size - 1 && flags; i++) {
		for (j = 0; j < size - i - 1; j++) {
			flags = FALSE;
			if (arr[j] > arr[j+1]) {
				swap(arr[j], arr[j+1]);
				flags = TRUE;
			}
		}
	}
}

int main(void)
{
	int i;
	int arr[ARRAY_SIZE] = { 7, 2, 4, 2, 64, 42, 1, 54, 4, 1 };

	bubble_sort(arr, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
