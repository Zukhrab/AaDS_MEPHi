//
//  main.c
//  LinkedList
//
//  Created by Зухраб Асаханов on 11.10.2022.
//
#include "list.h"

int main()
{
    Item *str;
    
    while((void)puts("\nEnter string:"), getList(&str))
    {
        deleteSpace(&str);
        deleteFirstChar(&str);
        printList(str);
        str = deleteList(str);
    }
    
    return 0;
}
