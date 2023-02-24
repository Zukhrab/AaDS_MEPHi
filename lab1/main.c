#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int getInt(int* a)
{
	int n;
	do
	{
		n = scanf("%d", a, sizeof(int));
		if (n < 0) return 0;
		if (n == 0)
		{
			printf("Error, repeat !\n");
			scanf("%*c", 0);
		}
	} while (n == 0);
	return 1;
}

int myPow(int x, int y)
{
	int count;
	for (count = 0; count < y - 1; count++)
		x = x * 10;

	return x;
}

int swap(int number)
{
	int tmp = number;
	int first, last, len = 0;

	last = tmp % 10;

	while (tmp)
	{
		first = tmp;
		tmp = tmp / 10;
		len += 1;
	}

	if (len == 1)
		return number;

	int powItem1 = myPow(first, len);
	int powItem2 = myPow(last, len);
	number = number - powItem1 - last;
	number = number + first + powItem2;

	return number;
}

void changeArray(int* array, int n)
{
	int count;
	for (count = 0; count < n; count++)
		array[count] = swap(array[count]);
}


void arraySort(int* array, int n)
{
	int tmp;
	int stop;

	for (int i = n - 1; i >= 0; i--)
	{
		stop = 1;
		for (int j = 0; j < i; j++)
		{
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				stop = 0;
			}
		}
		if (stop == 1)
			break;
	}
}

int main()
{
	int n;
	int count;

	puts("\nEnter number of elements");
	if ((getInt(&n)) == 0)
		return 0;

	puts("\nEnter your array");
	int* in_arr = (int*)malloc(sizeof(int) * n);
	for (count = 0; count < n; count++)
	{
		if ((getInt(&in_arr[count])) == 0)
			return 0;
		if (in_arr[count] < 0)
			return 0;
	}
	puts("");

	printf("Your array --> ");
	for (count = 0; count < n; count++)
		printf("%d ", in_arr[count]);
	puts("");

	changeArray(in_arr, n);
	printf("Before sorting --> ");
	for (count = 0; count < n; count++)
		printf("%d ", in_arr[count]);
	puts("");

	arraySort(in_arr, n);
	printf("After sorting --> ");
	for (count = 0; count < n; count++)
		printf("%d ", in_arr[count]);
	puts("");

	return 1;
}