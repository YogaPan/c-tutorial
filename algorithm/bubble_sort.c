#include <stdio.h>

#define ARRAY_SIZE 10

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

void bubble_sort(int *arr);

int main(void)
{
	int i;
	int arr[ARRAY_SIZE] = { 7, 2, 4, 2, 64, 42, 1, 54, 4, 1 };

	bubble_sort(arr);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d\n", arr[i]);

	return 0;
}

void bubble_sort(int *arr)
{
	int i;
	int j;

	for (i = 0; i < ARRAY_SIZE - 1; i++) {
		for (j = 0; j < ARRAY_SIZE - i - 1; j++) {
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
		}
	}
}
