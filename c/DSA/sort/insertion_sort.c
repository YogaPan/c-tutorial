#include <stdio.h>

#define ARRAY_SIZE 10

void insertion_sort(int *array, int size)
{
	int tmp;
	int i, j;

	for (i = 1; i < size; i++) {
		tmp = array[i];

		for (j = i; j > 0 && tmp < array[j-1]; j--)
			array[j] = array[j-1];

		array[j] = tmp;
	}
}

int main(void)
{
	int i;
	int array[ARRAY_SIZE] = { 5, 42, 99, 12, 51, 88, 43, 61, 49, 22 };

	insertion_sort(array, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
}
