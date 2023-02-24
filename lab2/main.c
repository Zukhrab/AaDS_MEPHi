#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

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

int getFloat(float* a)
{
	int n;
	do
	{
		n = scanf("%f", a, sizeof(float));
		if (n < 0) return 0;
		if (n == 0)
		{
			printf("Error, repeat !\n");
			scanf("%*c", 0);
		}
	} while (n == 0);
	return 1;
}

float min(float line[], int m)
{
	int t = m;
	float res = *line;
	for (; t-- > 0; ++line)
		if (*line < res)
			res = *line;

	return res;
}

float max(float line[], int m)
{
	int t = m;
	float res = *line;
	for (; t-- > 0; ++line)
		if (*line > res)
			res = *line;

	return res;
}

void erase(matrix* a)
{
	int i;
	for (i = 0; i < a->numbOfLines; ++i)
		free(a->lines[i].elements);
	free(a->lines);
	a->numbOfLines;
	a->lines = NULL;
}

void output1(matrix* a)
{
	int i;
	int s;
	
	for (i = 0; i < a->numbOfLines; i++)
	{
		for (s = 0; s < a->lines[i].numOfElem; s++)
			printf("%f ", a->lines[i].elements[s]);
		printf("\n");
	}
}

void changeMT(matrix* a)
{
	float minimum, maximum;
	int i, s;

	for (i = 0; i < a->numbOfLines;)
	{
		minimum = min(a->lines[i].elements, a->lines[i].numOfElem);
		maximum = max(a->lines[i].elements, a->lines[i].numOfElem);

		for (s = 0; s < a->lines[i].numOfElem;)
		{
			if (a->lines[i].elements[s] == minimum)
				a->lines[i].elements[s] = maximum;
			else if (a->lines[i].elements[s] == maximum)
				a->lines[i].elements[s] = minimum;
			s++;
		}
		i++;
	}
}

int input(matrix* mt)
{
	const char* pr = "";
	int m; // количество строк в матрице 
	int i, j;
	float* p;

	do
	{
		printf("%s\n", pr);
		printf("Enter number of lines --> ");
		pr = "Error, repeat !";

		if (getInt(&m) == 0) return 0;
	} while (m < 1);

	mt->numbOfLines = m;
	mt->lines = (line*)calloc(m, sizeof(line));

	for (i = 0; i < mt->numbOfLines; ++i)
	{
		pr = "";
		do
		{
			printf("%s\n", pr);
			printf("Enter number of elements in %d line --> ", i + 1);
			pr = "Error, repeat !";

			if (getInt(&m) == 0)
			{
				mt->numbOfLines = i;
				erase(mt);
				return 0;
			}
		} while (m < 1);
		mt->lines[i].numOfElem = m;
		p = (float*)malloc(sizeof(float) * m);
		mt->lines[i].elements = p;

		printf("Enter items for matrix line \n");
		for(j = 0; j < m; ++j, ++p)
			if (getFloat(p) == 0)
			{
				mt->lines = i + 1;
				erase(mt);
				return 0;
			}
	}
	return 1;
}

int main()
{
	printf("\n\t\t\t\t\t Laboratory work #1\n");
	matrix Matrix = { 0, NULL };
	float result;

	if (input(&Matrix) == 0)
	{
		printf("Error, end of file, repeat !");
		return 1;
	}
	printf("\nInput matrix\n");
	output1(&Matrix);
	changeMT(&Matrix);

	printf("\nOutput matrix\n");
	output1(&Matrix);

	return 1;
}