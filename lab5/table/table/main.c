//
//  main.c
//  table
//
//  Created by Зухраб Асаханов on 25.09.2023.
//

#include "table.h"

int main(int argc, const char * argv[])
{
    Table* tbl = NULL;
    tbl = initialize(tbl);
    int choice, kkey, rrelease;
    char* sstr = NULL;
    while(1)
    {
        puts(
             "1. Insert\n"
             "2. Find (1)\n"
             "3. Find (2)\n"
             "4. Delete (1)\n"
             "5. Delete (2)\n"
             "6. Show\n"
             "7. Exit"
             );
        printf("Please, make your choice -> ");
        getInt(&choice);
        switch (choice)
        {
            case 1:
                printf("\nPlease, enter your key -> ");
                getInt(&kkey);
                printf("Please, enter your information -> ");
                sstr = getStr();
                tbl = insert(kkey, sstr, tbl);
                break;
            case 2:
                printf("\nPlease, enter your key -> ");
                getInt(&kkey);
                find1(kkey, tbl);
                puts("");
                break;
            case 3:
                printf("\nPlease, enter your key -> ");
                getInt(&kkey);
                printf("Please, enter your realese -> ");
                getInt(&rrelease);
                find2(kkey, rrelease, tbl);
                puts("");
                break;
            case 4:
                printf("\nPlease, enter your key -> ");
                getInt(&kkey);
                del1(kkey, tbl);
                puts("");
                break;
            case 5:
                printf("\nPlease, enter your key -> ");
                getInt(&kkey);
                printf("Please, enter your realese -> ");
                getInt(&rrelease);
                del2(kkey, rrelease, tbl);
                puts("");
                break;
            case 6:
                show(tbl);
                break;
            case 7:
                tbl->itemsCount = 0;
                return 0;
                break;
            default:
                return -1;
        }
    }
    return 1;
}

// Не работало добавление элементов после удаления и присваивания поле busy -1

