#include <stdio.h>

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

void quick_sort(int *array, int left, int right)
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
