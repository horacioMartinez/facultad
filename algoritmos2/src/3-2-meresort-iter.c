#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int low, int high, int mid)
{
	int i, j, k, c[50];
	i = low;
	j = mid + 1;
	k = low;
	while ((i <= mid) && (j <= high))
	{
		if (a[i] < a[j])
		{
			c[k] = a[i];
			k++;
			i++;
		}
		else
		{
			c[k] = a[j];
			k++;
			j++;
		}
	}
	while (i <= mid)
	{
		c[k] = a[i];
		k++;
		i++;
	}
	while (j <= high)
	{
		c[k] = a[j];
		k++;
		j++;
	}
	for (i = low; i < k; i++)
	{
		a[i] = c[i];
	}
}

#define DIVIDE  0
#define CONQUER 1

void mergesort(int a[], int low, int high)
{
	int stack[1024];

	int i = 0;
	stack[i++] = low;
	stack[i++] = high;
	stack[i++] = DIVIDE;

	while (i > 0) {
		int op = stack[--i];
		int mid;

		if (op == DIVIDE) {
			high = stack[--i];
			low = stack[--i];
			
			if (low < high) {
				mid = (low + high) / 2;

				// merge(a, low, high, mid);
				stack[i++] = low;
				stack[i++] = high;
				stack[i++] = mid;
				stack[i++] = CONQUER;

				// mergesort(a, mid + 1, high);
				stack[i++] = mid + 1;
				stack[i++] = high;
				stack[i++] = DIVIDE;
				
				// mergesort(a, low, mid);
				stack[i++] = low;
				stack[i++] = mid;
				stack[i++] = DIVIDE;
			}
		}
		else if (op == CONQUER) {
			mid = stack[--i];
			high = stack[--i];
			low = stack[--i];
			merge(a, low, high, mid);
		}
	}
}

int main(int argc, char** argv)
{
	int arr[] = { 5, 8, 12, 9, 2, 7, -1, 9 };
	mergesort(arr, 0, 7);
	printf("mergesort iterativo: ");
	for (int i = 0; i <=7; i++) printf("%d ", arr[i]);
}

