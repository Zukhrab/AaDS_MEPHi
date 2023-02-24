#include "f1.h"

int main()
{
	vqueue VQ; int vchoice = 0; int vkey = 0;
	lqueue LQ; int lchoice = 0; int lkey = 0;

	int rc = 0;
	while (puts("\n1. Vector\n2. List"), getInt(&rc))
	{
		switch (rc)
		{
			case 1:
				vInit(&VQ);
				while (puts("\n1. Insert\n2. Print\n3. Remove\n4. Exit"), getInt(&vchoice))
					switch (vchoice)
					{
						case 1:
							puts("Your key");
							getInt(&vkey);
							vInsert(&VQ, vkey);
							vkey = 0;
							break;
						case 2:
							puts("Printing...");
							vPrint(&VQ); puts("");
							break;
						case 3:
							puts("Removing...\n");
							vRemove(&VQ);
							break;
						case 4:
							return 0;
							break;
						default:
							break;
					}
				break;
			case 2:
				lInit(&LQ);
				while (puts("\n1. Insert\n2. Print\n3. Remove\n4. Exit"), getInt(&lchoice))
					switch (lchoice)
					{
						case 1:
							puts("Your key");
							getInt(&lkey);
							lInsert(&LQ, lkey);
							lkey = 0;
							break;
						case 2:
							puts("Printing...");
							lPrint(&LQ); puts("");
							break;
						case 3:
							puts("Removing...\n");
							lRemove(&LQ);
							break;
						case 4:
							return 0;
							break;
						default:
							break;
					}
				break;
			default:
				puts("Error, repeat !");
				break;
		}
	}
	return 0;
}