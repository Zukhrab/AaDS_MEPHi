//
//  main.c
//  BlackRedTree
//
//  Created by Зухраб Асаханов on 07.02.2023.
//
#include "table.h"


int main(void)
{
    Table* table = NULL;
    table = tableInitialize(table);
    
    int choice = 1;
    printf(
        "1 - Input \n2 - Delete \n3 - Find \n4 - Show in order\n5 - Return max element\n6 - Quit \nPlease "
        "enter the choice - ");
    getInt(&choice);
    while (choice)
    {
        switch (choice)
        {
            case 1:
                table = tableInsert(table);
                break;
            case 2:
                table = tableDelete(table);
                break;

            case 3:
                tableSearch(table);
                break;
                
            case 4:
                tablePrintf(table);
                break;
                
            case 5:
                tableReturnMax(table);
                break;
                
            default:
                return 0;
        }
                
        printf(
               "1 - Input \n2 - Delete \n3 - Find \n4 - Show in order\n5 - Return max element\n6 - Quit \nPlease "
               "enter the choice - ");
        getInt(&choice);
    }
}
