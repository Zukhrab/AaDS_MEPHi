//
//  table.h
//  table
//
//  Created by Зухраб Асаханов on 25.09.2023.
//

#ifndef table_h
#define table_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

// STRUCT Info
typedef struct Info
{
    int release;                                                //* item version number *//
    char* info;                                                 //* pointer to information *//
    struct Info* next;                                          //* pointer to next information list node *//
} Info;

// STRUCT Item
typedef struct Item
{
    int busy;                                                   //* element busy sign *//
    int key;                                                    //* element key *//
    Info* info;                                                 //* pointer to information *//
} Item;

// STRUCT Table
typedef struct Table
{
    int itemsCount;
    Item items[SIZE];
} Table;

int getInt(int* a);
char* getStr(void);
Table* initialize(Table* t);
int hashFunc(int key);
Table* insert(int key, char* str, Table* t);
void find1(int key, Table* t);
void find2(int key, int release, Table* t);
void show(Table* t);
int isEmpty(Table* t);
int isFull(Table* t);
Table* del1(int key, Table* t);
Table* del2(int key, int release, Table* t);




#endif /* table_h */
