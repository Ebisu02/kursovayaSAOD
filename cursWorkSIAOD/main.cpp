#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char Path[] = "../testBase4.dat";
const int Size = 4000;

// k = god poseleniya

// bd - nas punkt
struct record
{
	char fullName[32]; // <Surname>_<Name>_<Ot4estvo> // Primer - Петpов_Иван_Федоpович___________ 
	char streetAdress[18]; // Primer - Ленина______________
	short int numOfHouse; // nomer doma
	short int numOfFloor; // nomer kvartiri
	char dateOfSettling[10]; // data zaseleniya // Primer - 29-02-65 // Format: dd-mm-yy
};

// Словарь...
enum Order {
	BYDATEOFSETTLING,
	BYSTREETNAME
};

// Честно - хер знает зачем я это высрал, пытался как-то сравнить дату в формате dd-mm-yy полностью
// Но пока что забил хер, т.к. сильно влияет на трудоемкость и время и скорость и вообще... Ебал я в рот это на плюсах делать!
int charToInt(char* simbol1)
{
	return stoi(simbol1); 
}

// Тоже сортировка, а именно формирование кучи... Было лень делать 2 отдельные для 2 разных случаев, поэтому сделал словарь
// Для данной ситуёвины, очень ленивый я, уж извините, знаю, что это плохой тон =)
void makeHeap(int arr[], int size, int i, record* data, Order order)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (order == BYDATEOFSETTLING)
	{
		if (l < size)
		{
			if (data[arr[l]].dateOfSettling[7] > data[arr[largest]].dateOfSettling[7])
			{
				largest = l;
			}
		}

		if (r < size)
		{
			if (data[arr[r]].dateOfSettling[7] > data[arr[largest]].dateOfSettling[7])
			{
				largest = r;
			}
		}
	}
	if (order == BYSTREETNAME) {
		if (l < size && data[arr[l]].streetAdress[0] >= data[arr[largest]].streetAdress[0])
		{
			largest = l;
		}
		if (r < size && data[arr[r]].streetAdress[0] >= data[arr[largest]].streetAdress[0])
		{
			largest = r;
		}
	}
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		makeHeap(arr, size, largest, data, order);
	}

}

// Сортировка, пирамидальная, не подходит она тут вообще... Но... Такое задание =)
void indexSort(record* data, int* arr, int size, Order order)
{
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		makeHeap(arr, size, i, data, order);
	}
	for (int i = size - 1; i >= 0; --i)
	{
		swap(arr[0], arr[i]);
		makeHeap(arr, i, 0, data, order);
	}
}

// Выводит БД по индексному массиву 
void printRecordByIndexArray(int* indexArray, int size)
{
	FILE* fileOut;
	fopen_s(&fileOut, Path, "rb");
	record recordBuffer[Size] = { 0 };
	int counter = 0;
	counter = fread((record*)recordBuffer, sizeof(record), Size, fileOut);
	cout << "FullName                        |" << "Street Name        |" << "House Number|" << "Floor number|" << "Date of Settling|" << "\n";
	cout << "--------------------------------|-------------------|------------|------------|----------------|\n";
	for (int i = 0; i < size; ++i)
	{
		cout << recordBuffer[indexArray[i]].fullName << " | " << recordBuffer[indexArray[i]].streetAdress << " | " << recordBuffer[indexArray[i]].numOfHouse << " \t | " << recordBuffer[indexArray[i]].numOfFloor << "\t      | " << recordBuffer[indexArray[i]].dateOfSettling << "      |" << "\n";
	}
	fclose(fileOut);
}


// Поиск, выводит таблицу элементов, найденных по заданному ключу
void findByYearOfSettling(int* indexArray, record* data, int size, char* key)
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		char bufForCompare[2] = "";
		bufForCompare[0] = data[indexArray[mid]].dateOfSettling[6];
		bufForCompare[1] = data[indexArray[mid]].dateOfSettling[7];
		if (bufForCompare[0] == key[0] && bufForCompare[1] == key[1])
		{
			cout << "\n\n\nFullName                        |" << "Street Name        |" << "House Number|" << "Floor number|" << "Date of Settling|" << "\n";
			cout << "--------------------------------|-------------------|------------|------------|----------------|\n";
			cout << data[indexArray[mid]].fullName << " | " << data[indexArray[mid]].streetAdress << " | " << data[indexArray[mid]].numOfHouse << " \t | " << data[indexArray[mid]].numOfFloor << "\t      | " << data[indexArray[mid]].dateOfSettling << "      |" << "\n";
			int flag = 2;
			int gRight = mid + 1;
			int gLeft = mid - 1;
			while (flag >= 1)
			{
				if (gRight < size)
				{
					char bufForCompareRight[2];
					bufForCompareRight[0] = data[indexArray[gRight]].dateOfSettling[6];
					bufForCompareRight[1] = data[indexArray[gRight]].dateOfSettling[7];
					if (bufForCompareRight[0] == key[0] && bufForCompareRight[1] == key[1])
					{
						cout << data[indexArray[gRight]].fullName << " | " << data[indexArray[gRight]].streetAdress << " | " << data[indexArray[gRight]].numOfHouse << " \t | " << data[indexArray[gRight]].numOfFloor << "\t      | " << data[indexArray[gRight]].dateOfSettling << "      |" << "\n";
						++gRight;
					}
					else
					{
						flag--;
					}
				}
				if (gLeft >= 0)
				{
					char bufForCompareLeft[2];
					bufForCompareLeft[0] = data[indexArray[gLeft]].dateOfSettling[6];
					bufForCompareLeft[1] = data[indexArray[gLeft]].dateOfSettling[7];
					if (bufForCompareLeft[0] == key[0] && bufForCompareLeft[1] == key[1])
					{
						cout << data[indexArray[gLeft]].fullName << " | " << data[indexArray[gLeft]].streetAdress << " | " << data[indexArray[gLeft]].numOfHouse << " \t | " << data[indexArray[gLeft]].numOfFloor << "\t      | " << data[indexArray[gLeft]].dateOfSettling << "      |" << "\n";
						--gLeft;
					}
					else {
						flag--;
					}
				}
			}
			return;
		}
		if (bufForCompare[0] < key[0] && bufForCompare[1] < key[1])
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	cout << "\n\nNot Found\n";
	return;
}

int main()
{
	FILE* fileOut; 
	fopen_s(&fileOut, Path, "rb");
	record recordBuffer[Size] = { 0 };
	int counter = 0;
	counter = fread((record*)recordBuffer, sizeof(record), Size, fileOut);
	for (int i = 0; i < 10; ++i)
	{
		cout << recordBuffer[i].fullName << " | " << recordBuffer[i].streetAdress << " | " << recordBuffer[i].numOfHouse << " | " << recordBuffer[i].numOfFloor << " | " << recordBuffer[i].dateOfSettling << "\n";
	}
	fclose(fileOut);

	cout << "\n\n";

	int* indexArray = new int[10];
	for (int i = 0; i < 10; ++i)
	{
		indexArray[i] = i;
	}
	indexSort(recordBuffer, indexArray, 10, BYDATEOFSETTLING);
	printRecordByIndexArray(indexArray, 10);

	char buf[2];

	buf[0] = '9';
	buf[1] = '4';

	findByYearOfSettling(indexArray, recordBuffer, 10, buf);

	system("PAUSE");
	return 0;
}