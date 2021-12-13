using namespace std;

#include "part_1.h"
#include "part_2.h"
#include "part_3.h"
#include "part_4.h"

void menu()
{
	int arr[Size];
	record recArray[Size] = { 0 };
	int c = 0;
	FILE* file;
	fopen_s(&file, Path, "rb");
	c = fread((record*)recArray, sizeof(record), Size, file);
	int indArray[Size];
	for (int i = 0; i < Size; ++i)
	{
		indArray[i] = i;
	}

	cout << "Menu\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records\n3.Find a records by key\n4.Print code table\n0.Exit\n";
	int choose = 0;
	while (cin >> choose)
	{
		if (choose == 1)
		{
			print_record(recArray, Size);
		}
		if (choose == 2)
		{
			index_sort(recArray, indArray, Size);
			print_record_by_index_array(indArray, recArray, Size);
		}
		if (choose == 3)
		{
			char key[2];
			cout << "\nEnter a key:";
			cin >> key;
			int bIndArray[Size];
			for (int i = 0; i < Size; ++i)
			{
				bIndArray[i] = i;
			}
			index_sort(recArray, bIndArray, Size);
			find_by_year_of_settling(bIndArray, recArray, Size, key);
		}
		if (choose == 4)
		{
			std::ifstream bfile(Path, std::ios::binary);
			decode(bfile);
			bfile.close();
		}
		if (choose == 0)
		{
			exit(1);
		}
		cout << "\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records\n3.Find a records by key\n4.Print code table\n0.Exit\n";
	}
	fclose(file);
}

int main()
{
	menu();
	system("PAUSE");
	return 0;
}