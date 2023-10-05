//
//  table.c
//  table
//
//  Created by Зухраб Асаханов on 25.09.2023
//

#include "table.h"

int getInt(int* a)
{
    int n;
    do
    {
        n = scanf("%d", a);
        if (n < 0) return 0;
        if (n == 0)
        {
            printf("Error, repeat !\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

char* getStr(void)
{
    char* ptr = (char*)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do
    {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else
        {
            len += strlen(buf);
            ptr = (char*)realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n == 0);
    
    return ptr;
}

Table* initialize(Table* t)
{
    t = (Table*)malloc(sizeof(Table));
    t->itemsCount = 0;
    for(int i = 0; i < SIZE; i++)
        t->items[i].busy = 0;
    
    return t;
}

int hashFunc(int key)
{
    return key % SIZE;
}

Table* insert(int key, char* str, Table* t)
{
    int switcher = 0;
    int hash;
    hash = hashFunc(key);
    
    Info* tmp = NULL;
    Info* leaping = NULL;
    
    // Если не возникло коллизии, то
    if (t->items[hash].busy == 0)        // Если признак занятости элемента равен 0
    {
        t->items[hash].key = key;
        t->items[hash].info = (Info*)malloc(sizeof(Info));
        t->items[hash].info->release = 1;
        t->items[hash].info->info = str;
        t->items[hash].info->next = NULL;
        t->items[hash].busy = 1;
        
        t->itemsCount++;
        puts("Key inserted successfully\n");
        return t;
    }
    if (t->items[hash].busy == 1)
    {
        // Если возникла коллизия и ключи не совпали, то
        if(t->items[hash].key != key)
        {
//            do
//            {
//                
//            }while(t->items[hash].busy = -1 && );
            // Тут надо разделить на два случая, когда следующий по хэшу элемент есть и когда его нет
            do
            {
                hash = (hash + 7) % SIZE;
                if(t->items[hash].busy == 1 && t->items[hash].key == key)
                {
                    int lastRelease = 0;
                    tmp = t->items[hash].info;
                    while(tmp != NULL)
                    {
                        lastRelease = tmp->release;
                        tmp = tmp->next;
                    }
                    
                    tmp = (Info*)malloc(sizeof(Info));
                    tmp->release = lastRelease + 1;
                    tmp->info = str;
                    tmp->next = NULL;
                    
                    leaping = t->items[hash].info;
                    while(leaping->next)
                        leaping = leaping->next;

                    leaping->next = tmp;
                    
                    t->itemsCount++;
                    puts("Key inserted successfully\n");
                    return t;
                }
            } while(t->items[hash].busy);

            t->items[hash].key = key;
            t->items[hash].info = (Info*)malloc(sizeof(Info));
            t->items[hash].info->release = 1;
            t->items[hash].info->info = str;
            t->items[hash].info->next = NULL;
            t->items[hash].busy = 1;

            t->itemsCount++;
            puts("Key inserted successfully\n");
            return t;
        }
        // Если возникла коллизия и совпали ключи, то
        if(t->items[hash].key == key)
        {
            int lastRelease = 0;
            tmp = t->items[hash].info;
            while(tmp != NULL)
            {
                lastRelease = tmp->release;
                tmp = tmp->next;
            }
            
            tmp = (Info*)malloc(sizeof(Info));
            tmp->release = lastRelease + 1;
            tmp->info = str;
            tmp->next = NULL;
            
            leaping = t->items[hash].info;
            while(leaping->next)
                leaping = leaping->next;

            leaping->next = tmp;
            
            t->itemsCount++;
            puts("Key inserted successfully\n");
            return t;
        }
    }
    
    for(int i = 0; i < SIZE; i++)
        if(t->items[i].busy == 1)
            if(t->items[i].key == key)
                switcher = 1;

    if(t->items[hash].busy == -1 && switcher == 1)
    {
        while(t->items[hash].key != key)
            hash = (hash + 7) % SIZE;
        
        int lastRelease = 1;
        tmp = t->items[hash].info;
        while(tmp->next != NULL)
        {
            lastRelease = tmp->release;
            tmp = tmp->next;
        }
        
        tmp = (Info*)malloc(sizeof(Info));
        tmp->release = lastRelease + 1;
        tmp->info = str;
        tmp->next = NULL;
        
        leaping = t->items[hash].info;
        while(leaping->next)
            leaping = leaping->next;

        leaping->next = tmp;
        
        t->itemsCount++;
        puts("Key inserted successfully\n");
        return t;
    }
    else
    {
        t->items[hash].key = key;
        t->items[hash].info = (Info*)malloc(sizeof(Info));
        t->items[hash].info->release = 1;
        t->items[hash].info->info = str;
        t->items[hash].info->next = NULL;
        t->items[hash].busy = 1;
        
        t->itemsCount++;
        puts("Key inserted successfully\n");
        return t;
    }
    return t;
}

void show(Table* t)
{
    Info* tmp = NULL;
    for(int i = 0; i < SIZE; i++)
    {
        if(t->items[i].busy == 1)
        {
            int rkey = t->items[i].key;
            tmp = t->items[i].info;
            printf("%d: %d: %d -> ", i, t->items[i].busy, rkey);
            while(tmp != NULL)
            {
                printf("(%d: %s) ", tmp->release, tmp->info);
                tmp = tmp->next;
            }
            puts("");
        }
        else
            printf("%d: %d\n", i, t->items[i].busy);
    }
    puts("");
}


void find1(int key, Table* t)
{
    int hash;
    hash = hashFunc(key);
    Info* tmp = NULL;
    
    // Разберем три случая которые могут возникнуть:
    // 1. Если ключ находится в искомом индексе(hash), то
    if (t->items[hash].busy == 1 || t->items[hash].busy == -1)        // Если признак занятости элемента равен 1
    {
        if(key == t->items[hash].key)
        {
            tmp = t->items[hash].info;
            while(tmp->next)
            {
                printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                tmp = tmp->next;
            }
            printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
        }
        else
        {
            while(t->items[hash].busy || t->items[hash].busy == -1)
            {
                hash = (hash + 7) % SIZE;
                if(key == t->items[hash].key)
                {
                    tmp = t->items[hash].info;
                    while(tmp->next)
                    {
                        printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                        tmp = tmp->next;
                    }
                    printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                    return ;
                }
            }
        }
        return ;
    }
    else
        puts("There is no such key\n");
    return ;
}
void find2(int key, int release, Table* t)
{
    int hash;
    hash = hashFunc(key);
    Info* tmp = NULL;
    
    // Разберем три случая которые могут возникнуть:
    // 1. Если ключ находится в искомом индексе(hash), то
    if (t->items[hash].busy == 1 || t->items[hash].busy == -1)        // Если признак занятости элемента равен 1
    {
        if(key == t->items[hash].key)
        {
            tmp = t->items[hash].info;
            while(tmp)
            {
                if(tmp->release == release)
                {
                    printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                    return ;
                }
                tmp = tmp->next;
            }
        }
        else
        {
            while(t->items[hash].busy || t->items[hash].busy == -1)
            {
                hash = (hash + 7) % SIZE;
                if(key == t->items[hash].key)
                {
                    tmp = t->items[hash].info;
                    while(tmp->next)
                    {
                        printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                        tmp = tmp->next;
                    }
                    printf("Key: %d |∞| Release: %d |∞| Info: %s\n", key, tmp->release, tmp->info);
                    return ;
                }
            }
        }
        return ;
    }
    else
        puts("There is no such key\n");
    return ;
}

Table* del1(int key, Table* t)
{
    int hash;
    hash = hashFunc(key);
    
    Info* tmp = NULL;
    Info* leaping = NULL;
    
    // Разберем три случая которые могут возникнуть:
    // 1. Если ключ находится в искомом индексе(hash), то
    if (t->items[hash].busy == 1)        // Если признак занятости элемента равен 1
    {
        if(key == t->items[hash].key)   // Если ключи совпали
        {
            tmp = t->items[hash].info;
            leaping = t->items[hash].info;
            
            while(tmp->next != NULL)
            {
                while(leaping->next->next)
                    leaping = leaping->next;
                
                free(leaping->info);
                leaping->release = 0;
                leaping->next = NULL;
                
                t->itemsCount--;
                leaping = tmp;
            }
            t->items[hash].busy = -1;
            t->items[hash].key = 0;
            free(t->items[hash].info);
            return t;
        }
        else                            // Если не совпали бегаем пока не встретим пустую строчку
        {
            while(t->items[hash].busy)
            {
                hash = (hash + 7) % SIZE;
                if(key == t->items[hash].key)
                {
                    tmp = t->items[hash].info;
                    leaping = t->items[hash].info;
                    
                    while(tmp->next != NULL)
                    {
                        while(leaping->next->next)
                            leaping = leaping->next;
                        
                        free(leaping->info);
                        leaping->release = 0;
                        leaping->next = NULL;
                        
                        t->itemsCount--;
                        leaping = tmp;
                    }
                    t->items[hash].busy = -1;
                    t->items[hash].key = 0;
                    free(t->items[hash].info);
                    return t;
                }
            }
        }
        return t;
    }
    else
        puts("There is no such key\n");
    
    return t;
}

Table* del2(int key, int release, Table* t)
{
    int hash;
    hash = hashFunc(key);
    
    Info* tmp = NULL;
    Info* leaping = NULL;
    
    // Разберем три случая которые могут возникнуть:
    // 1. Если ключ находится в искомом индексе(hash), то
    if (t->items[hash].busy == 1 || t->items[hash].busy == -1)        // Если признак занятости элемента равен 1
    {
        if(key == t->items[hash].key)   // Если ключи совпали
        {
            leaping = t->items[hash].info;
            
            while(leaping->next->release != release)
                leaping = leaping->next;
            
            free(leaping->next->info);
            leaping->next->release = 0;
            tmp = leaping->next->next;
            leaping->next->next = NULL;
            leaping->next = tmp;
            
            t->itemsCount--;
            return t;
        }
        else                            // Если не совпали бегаем пока не встретим пустую строчку
        {
            while(t->items[hash].busy)
            {
                hash = (hash + 7) % SIZE;
                if(key == t->items[hash].key)   // Если ключи совпали
                {
                    leaping = t->items[hash].info;
                    
                    while(leaping->next->release != release)
                        leaping = leaping->next;
                    
                    free(leaping->next->info);
                    leaping->next->release = 0;
                    tmp = leaping->next->next;
                    leaping->next->next = NULL;
                    leaping->next = tmp;
                    
                    t->itemsCount--;
                    return t;
                }
            }
            return t;
        }
    }
    else
        puts("There is no such key\n");
    
    return t;
}


