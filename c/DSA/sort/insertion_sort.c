#include <stdio.h>

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
	int array[ARRAY_SIZE];
	FILE *fp;

	fp = fopen(RANDOM_FILE, "r");

	for (i = 0; i < ARRAY_SIZE; i++)
		fscanf(fp, "%d", &array[i]);

	insertion_sort(array, ARRAY_SIZE);

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");

	fclose(fp);

	return 0;
}
