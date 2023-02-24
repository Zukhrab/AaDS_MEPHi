#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <malloc.h>

typedef struct line
{
	int numOfElem;
	float* elements;
}line;

typedef struct matrix
{
	int numbOfLines;
	line* lines;
}matrix;

#endif 