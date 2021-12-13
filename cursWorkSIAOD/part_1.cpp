#include "part_1.h"

void print_record(record* Array, int size)
{
	int counter = 0;
	for (int i = 0; i < size; ++i, ++counter)
	{
	next:
		cout << Array[i].fullName << " \t| " << Array[i].streetAdress << " \t| " << Array[i].numOfHouse << " \t| " << Array[i].numOfFloor << " \t| " << Array[i].dateOfSettling << "\n";
		if (counter == 20)
		{
			counter = 0;
			cout << "\nIf u wanna see next page - write '1', if not - write '0'\n";
			int chs = -1;
			cin >> chs;
			if (chs == 0)
			{
				return;
			}
			else if (chs == 1)
			{
				goto next;
			}
			else
			{
				cout << "\nInvalid choice\n";
			}
		}
	}
}