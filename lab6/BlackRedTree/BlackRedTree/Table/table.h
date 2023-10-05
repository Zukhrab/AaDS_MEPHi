//
//  table.h
//  BlackRedTree
//
//  Created by Зухраб Асаханов on 11.09.2023.
//

#ifndef table_h
#define table_h

#include "tree.h"
#define SIZE 3

typedef struct item
{
    int busy;
    int key;
    Node* info;
} item;

typedef struct cache
{
    int top;
    item element[SIZE];
} cache;

cache* cacheInit(cache* c);
cache* cacheInsert(int key, Node* root, cache* c);
cache* cacheDelete(cache* c);
int cacheSearch(cache* c);
void cacheShow(cache* c);
int hashFunc(int key);
int match(int k, cache* c);

typedef struct Table
{
    cache* cache;          // Создается хэш - таблица
    Node* root;          // Создается корень дерева
    Node* tmp;
} Table;

// task funcs
Table* tableInsert(Table* table);
Table* tableDelete(Table* table);
void tableSearch(Table* table);
void tablePrintf(Table* table);
void tableReturnMax(Table* table);

//main
Table* tableInitialize(Table* table);


#endif /* table_h */
