#ifndef F1_H
#define F1_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QMAX 10


// VECTOR STRUCTURE

typedef struct vqueue
{
	int qu[QMAX];
	int rear, frnt;
}vqueue;


// LIST STRUCTURE

typedef struct list
{
	int field;
	struct list *ptr;
}list;

typedef struct lqueue
{
	list *front;
	list *last;
}lqueue;

int getInt(int* a)
{
	int n = 0;
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


// VECTOR FUNCTIONS

void vInit(vqueue* q)
{
	q->frnt = 1;
	q->rear = 0;
}

void vInsert(vqueue* q, int x)
{
	if (q->rear < QMAX - 1)
	{
		q->rear++;
		q->qu[q->rear] = x;
	}
	else
		puts("Очередь полна!\n");

	return;
}

int vIsempty(vqueue* q)
{
	if (q->rear < q->frnt)
		return 1;
	else
		return 0;
}

void vPrint(vqueue* q)
{
	int h;
	if (vIsempty(q) == 1)
	{
		puts("Очередь пуста!\n");
		return;
	}
	for (h = q->frnt; h <= q->rear; h++)
		printf("%d ", q->qu[h]);
	return;
}

int vRemove(vqueue* q)
{
	int x, h;
	if (vIsempty(q) == 1)
	{
		puts("Очередь пуста!\n");
		return 0;
	}
	x = q->qu[q->frnt];
	for (h = q->frnt; h < q->rear; h++)
		q->qu[h] = q->qu[h + 1];
	q->rear--;

	return x;
}


// LIST FUNCTIONS

void lInit(lqueue* q)
{
	q->front = NULL;
	q->last = NULL;
} 

int lIsempty(lqueue* q)
{
	if (q->front == NULL)
		return 1;
	else
		return 0;
}

int lInsert(lqueue* q, int x)
{
	list* newnode = malloc(sizeof(list));

	if (newnode == NULL)
		return 0;

	newnode->field = x;
	newnode->ptr = NULL;

	if (q->last != NULL)
		q->last->ptr = newnode;
	q->last = newnode;
	if (q->front == NULL)
		q->front = newnode;

	return 1;
}

void lPrint(lqueue* q) {
	list* h;

	if (lIsempty(q) == 1)
		puts("Queue is empty!\n");

	for (h = q->front; h != NULL; h = h->ptr)
		printf("-%d-", h->field);
}

void lRemove(lqueue* q)
{
	if (lIsempty(q) == 1)
	{
		puts("Queue is empty!\n");
		return 0;
	}

	list* temp = q->front;
	int x = temp->field;

	q->front = q->front->ptr;

	if (q->front == NULL)
		q->last == NULL;

	free(temp);

	return x;
}

#endif
