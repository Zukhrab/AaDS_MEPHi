//
//  table.c
//  BlackRedTree
//
//  Created by Зухраб Асаханов on 11.09.2023.
//

#include "table.h"

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
int hashFunc(int key) { return key % SIZE; }                    // Функция распределения
cache* cacheInit(cache* c)                                      // Инициализация кэша
{
    c = (cache*)malloc(sizeof(cache));
    
    c->top = 0;
    for(int i = 0; i < SIZE; i++)
        c->element[i].busy = 0;
    
    return c;
}                                                               // Функция, которая проверяет существует ли передаваемый ключ в кэше
int matchHash(int key, cache* c)
{
    for(int i = 0; i < SIZE; i++)
        if(c->element[i].busy == 1)
            if(c->element[i].key == key)
                return 1;
    return 0;
}
cache* cacheInsert(int key, Node* root, cache* c)                                    // Функция включения элемента в кэш
{
    if(c->top == SIZE)                                                               // Если кэш заполнен, то будет о уведомление об этом и перезаписан 
    {
        puts("Cache is full. The cache value at current index will be overwritten into the tree");
        int hash = hashFunc(key);
        c->element[hash].key = key;
        c->element[hash].info = findNode(key, &root);
        c->element[hash].busy = 1;
      
        return c;
    }
        
    if(c->top == 0)                                                                  // Если в кэше ничего нет, то элемент запишется без проблем
    {
        int hash = hashFunc(key);
        c->element[hash].key = key;
        c->element[hash].info = root;
        c->element[hash].busy = 1;
        c->top++;
      
        return c;
    }
    
    int hash = hashFunc(key);
    if(c->element[hash].busy == 1)
        do hash++; while (c->element[hash].busy == 1);
    
    c->element[hash].key = key;
    c->element[hash].info = root;
    c->element[hash].busy = 1;
    c->top++;
    
    return c;
}
cache* cacheDelete(cache* c)                                    // Функция удаления элемента из кэша
{
    if(c->top == 0)
    {
        puts("Table is empty");
        return c;
    }
    
    int kkey;
    printf("Input key -> ");
    getInt(&kkey);
    
    if(matchHash(kkey, c))
    {
        int hash = hashFunc(kkey);
        if(c->element[hash].busy == 0)
            do hash++; while (c->element[hash].busy != 1);
        
        c->element[hash].key = 0;
        free(c->element[hash].info);
        c->element[hash].info = NULL;
        c->element[hash].busy = 0;
        c->top--;
        
        return c;
    }
    printf("There is no such key in the cache\n");
    return c;
}
int cacheSearch(cache* c)                                       // Функция нахождения элемента в кэше
{
    if(c->top == 0)
    {
        puts("Table is empty");
        return -1;
    }
    
    int kkey;
    
    printf("Input key -> ");
    getInt(&kkey);
    
    if(matchHash(kkey, c))
    {
        int hash = hashFunc(kkey);
        if(c->element[hash].busy == 0)
            do hash++; while (c->element[hash].busy != 1);
        
        printf("%d: %d: %d -> %s\n", hash, c->element[hash].busy, c->element[hash].key, c->element[hash].info->info);
        puts("");
        return 1;
    }
    printf("There is no such key in the cache\n");
    return 0;
}
void cacheShow(cache* c)                                        // Функция, показывающая весь кэш(существует для дебага)
{
    for(int i = 0; i < SIZE; i++)
        if(c->element[i].info != NULL)
            printf("%d: %d: %d -> %s\n", i, c->element[i].busy, c->element[i].key, c->element[i].info->info);
        else
            printf("%d: %d\n", i, c->element[i].busy);
    puts("");
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// general structure
Table* tableInitialize(Table* table)
{
    table = (Table*)malloc(sizeof(Table));
    table->cache = NULL;                                                                        // Создается хэш - таблица
    table->cache = cacheInit(table->cache);
    table->root = NULL;                                                                         // Создается корень дерева
    table->tmp = NULL;                                                                          // Временный элемент
    
    return table;
}

Table* tableInsert(Table* table)
{
    int scankeyue;
    char* sstr = NULL;

    printf("\nPlease enter a key value to insert - ");
    getInt(&scankeyue);
    printf("Please enter a info to insert - ");
    sstr = getStr();
    
    if (table->root == NULL)                                                                    // Если элемент первый то записываем в дерево как корень и в кэш как первый элемент
    {
        table->root = newNode(scankeyue, sstr, NULL);
        table->root->color = 0;
        cacheInsert(scankeyue, table->root, table->cache);                                      // Вставить в кэш ссылку на узел дерева(значение root) и вставить ключ
        printf("Successfully inserted %d in the tree\n\n", scankeyue);
    }
    else                                                                                        // Если элемент в дереве не первый
    {
        if((matchHash(scankeyue, table->cache)) || (findNode(scankeyue, &(table->root)) != NULL))
        {
            puts("Such a key already exists\n"); return table;
        }                                                                                       // Если в кэше присутствует такой же элемент как встaвляемый то выбрасываем ошибку
        else                                                                                    // Если ключи разные в кэше
        {
            table->tmp = insertNode(scankeyue, sstr, &(table->root));
            cacheInsert(scankeyue, table->root, table->cache);
            printf("Successfully inserted %d in the tree\n\n", scankeyue);
        }
    }
    return table;
}

Table* tableDelete(Table* table)
{
    int scankeyue;
    if((table->cache->top == 0) || (table->root == NULL))                                                              // Если таблица пуста, то удалять нечего - удаление из дерева
    {
        puts("The cache and tree is empty");
        return table;
    }
    
    printf("Please enter a key to delete - ");
    getInt(&scankeyue);
    
    
        
    if(matchHash(scankeyue, table->cache))                                                      // Если такой ключ есть в кэше, и удаляется через кэш
    {
        puts("The key is in the cache. And key will be delete from Node* in cacheItem");
        int hash = hashFunc(scankeyue);
        if(table->cache->element[hash].key != scankeyue)
            do hash++; while (table->cache->element[hash].key != scankeyue);
        
        deleteNode(scankeyue, &(table->root));
        //free(table->cache->element[hash].info->info);
        table->cache->element[hash].info->info = NULL;
        table->cache->element[hash].info->key = 0;
        table->cache->element[hash].key = 0;
        table->cache->element[hash].busy = 0;
        table->cache->element[hash].info = NULL;
        
        table->cache->top--;
    }
    else                                                                                        // Если такого ключа в кэше нет, то ищем в дереве - если нет ошибка
    {
        deleteNode(scankeyue, &(table->root));
        
    }
    return table;
}

void tableSearch(Table* table)
{
    int scankeyue;
    if(table->cache->top == 0 && table->root == NULL)
    {
        puts("\nCache and tree are empty\n");
        return;
    }
    
    printf("\nPlease enter a key to find - ");
    getInt(&scankeyue);
    
    if(matchHash(scankeyue, table->cache) == 1)                 // Если ключ найден в кэше, то
    {
        int hash = hashFunc(scankeyue);
        if(table->cache->element[hash].key != scankeyue)
            do hash++; while (table->cache->element[hash].key != scankeyue);
        
        printf("key: %d ||| color: %d ||| info: %s\n", table->cache->element[hash].key, table->cache->element[hash].info->color,
               table->cache->element[hash].info->info);
    }
    else
    {
        Node* tmp = NULL;
        tmp = findNode(scankeyue, &(table->root));
        if(tmp == NULL)
            printf("Node not found. The key does not exist\n");
        else
        {
            printf("key: %d ||| color: %d ||| info: %s\n\n", tmp->key, tmp->color, tmp->info);
            
            int hash = hashFunc(scankeyue);
            table->cache->element[hash].key = tmp->key;
            table->cache->element[hash].info = tmp;
        }
    }
}

void tablePrintf(Table* table)
{
    cacheShow(table->cache);
    printInorder(table->root, 0);
}

void tableReturnMax(Table* table) { printMaxElement(table->root); };
