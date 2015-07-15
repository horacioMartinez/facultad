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

void mergesort(int a[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergesort(a, low, mid);
		mergesort(a, mid + 1, high);
		merge(a, low, high, mid);
	}
}

int main(int argc, char** argv)
{
	int arr[] = { 5, 8, 12, 9, 2, 7, -1, 9 };
	mergesort(arr, 0, 7);
	printf("mergesort recursivo: ");
	for (int i = 0; i <=7; i++) printf("%d ", arr[i]);
}

