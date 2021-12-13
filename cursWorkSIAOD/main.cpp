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
	char fullName[32]; // <Surname>_<Name>_<Ot4estvo> // Primer - Ïåòpîâ_Èâàí_Ôåäîpîâè÷___________ 
	char streetAdress[18]; // Primer - Ëåíèíà______________
	short int numOfHouse; // nomer doma
	short int numOfFloor; // nomer kvartiri
	char dateOfSettling[10]; // data zaseleniya // Primer - 29-02-65 // Format: dd-mm-yy
};

// Ñëîâàðü...
enum Order {
	BYDATEOFSETTLING,
	BYSTREETNAME
};

// ×åñòíî - õåð çíàåò çà÷åì ÿ ýòî âûñðàë, ïûòàëñÿ êàê-òî ñðàâíèòü äàòó â ôîðìàòå dd-mm-yy ïîëíîñòüþ
// Íî ïîêà ÷òî çàáèë õåð, ò.ê. ñèëüíî âëèÿåò íà òðóäîåìêîñòü è âðåìÿ è ñêîðîñòü è âîîáùå... Åáàë ÿ â ðîò ýòî íà ïëþñàõ äåëàòü!
int charToInt(char* simbol1)
{
	return stoi(simbol1);
}

// Òîæå ñîðòèðîâêà, à èìåííî ôîðìèðîâàíèå êó÷è... Áûëî ëåíü äåëàòü 2 îòäåëüíûå äëÿ 2 ðàçíûõ ñëó÷àåâ, ïîýòîìó ñäåëàë ñëîâàðü
// Äëÿ äàííîé ñèòó¸âèíû, î÷åíü ëåíèâûé ÿ, óæ èçâèíèòå, çíàþ, ÷òî ýòî ïëîõîé òîí =)
void makeHeap(int arr[], int size, int i, record* data, Order order)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;


	if (order == BYDATEOFSETTLING)
	{
		char bufForLargestY[2];
		char bufForLargestM[2];
		char bufForLargestD[2];

		bufForLargestY[0] = data[arr[largest]].dateOfSettling[6];
		bufForLargestY[1] = data[arr[largest]].dateOfSettling[7];
		bufForLargestM[0] = data[arr[largest]].dateOfSettling[3];
		bufForLargestM[1] = data[arr[largest]].dateOfSettling[4];
		bufForLargestD[0] = data[arr[largest]].dateOfSettling[0];
		bufForLargestD[1] = data[arr[largest]].dateOfSettling[1];

		long int cLargest = charToInt(bufForLargestY) * 12 * 30 + charToInt(bufForLargestM) * 30 + charToInt(bufForLargestD);


		if (l < size)
		{
			char bufForLY[2];
			char bufForLM[2];
			char bufForLD[2];

			bufForLY[0] = data[arr[l]].dateOfSettling[6];
			bufForLY[1] = data[arr[l]].dateOfSettling[7];
			bufForLM[0] = data[arr[l]].dateOfSettling[3];
			bufForLM[1] = data[arr[l]].dateOfSettling[4];
			bufForLD[0] = data[arr[l]].dateOfSettling[0];
			bufForLD[1] = data[arr[l]].dateOfSettling[1];

			long int cL = charToInt(bufForLY) * 12 * 30 + charToInt(bufForLM) * 30 + charToInt(bufForLD);

			if (cL > cLargest)
			{
				largest = l;
			}
		}

		bufForLargestY[0] = data[arr[largest]].dateOfSettling[6];
		bufForLargestY[1] = data[arr[largest]].dateOfSettling[7];
		bufForLargestM[0] = data[arr[largest]].dateOfSettling[3];
		bufForLargestM[1] = data[arr[largest]].dateOfSettling[4];
		bufForLargestD[0] = data[arr[largest]].dateOfSettling[0];
		bufForLargestD[1] = data[arr[largest]].dateOfSettling[1];

		cLargest = (charToInt(bufForLargestY) * 12 * 30) + (charToInt(bufForLargestM) * 30) + charToInt(bufForLargestD);

		if (r < size)
		{

			char bufForRY[2];
			char bufForRM[2];
			char bufForRD[2];

			bufForRY[0] = data[arr[r]].dateOfSettling[6];
			bufForRY[1] = data[arr[r]].dateOfSettling[7];
			bufForRM[0] = data[arr[r]].dateOfSettling[3];
			bufForRM[1] = data[arr[r]].dateOfSettling[4];
			bufForRD[0] = data[arr[r]].dateOfSettling[0];
			bufForRD[1] = data[arr[r]].dateOfSettling[1];

			long int cR = charToInt(bufForRY) * 12 * 30 + charToInt(bufForRM) * 30 + charToInt(bufForRD);

			if (cR > cLargest)
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

// Ñîðòèðîâêà, ïèðàìèäàëüíàÿ, íå ïîäõîäèò îíà òóò âîîáùå... Íî... Òàêîå çàäàíèå =)
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

// Âûâîäèò ÁÄ ïî èíäåêñíîìó ìàññèâó 
void printRecordByIndexArray(int* indexArray, record* recordBuffer, int size)
{
	int counter = 0;
	cout << "FullName                        |" << "Street Name        |" << "House Number|" << "Floor number|" << "Date of Settling|" << "\n";
	cout << "--------------------------------|-------------------|------------|------------|----------------|\n";
	for (int i = 0; i < size; ++i)
	{
		if (counter - 20 == 0)
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
		next:
		++counter;
		cout << recordBuffer[indexArray[i]].fullName << " | " << recordBuffer[indexArray[i]].streetAdress << " | " << recordBuffer[indexArray[i]].numOfHouse << " \t | " << recordBuffer[indexArray[i]].numOfFloor << "\t      | " << recordBuffer[indexArray[i]].dateOfSettling << "      |" << "\n";
	}
}


// Ïîèñê, âûâîäèò òàáëèöó ýëåìåíòîâ, íàéäåííûõ ïî çàäàííîìó êëþ÷ó
void findByYearOfSettling(int* indexArray, record* data, int size, char* key)
{
	int left = 0;
	int right = size;
	int amountOfVariants = 0;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		char bufForCompare[2] = "";
		bufForCompare[0] = data[indexArray[mid]].dateOfSettling[6];
		bufForCompare[1] = data[indexArray[mid]].dateOfSettling[7];
		if (bufForCompare[0] == key[0] && bufForCompare[1] == key[1])
		{
			++amountOfVariants;
			cout << "\n\n\nFullName                        |" << "Street Name        |" << "House Number|" << "Floor number|" << "Date of Settling|" << "\n";
			cout << "--------------------------------|-------------------|------------|------------|----------------|\n";
			bool fLeft = true;
			int gLeft = mid - 1;
			while (fLeft)
			{
				if (gLeft >= 0)
				{
					char bufForCompareLeft[2];
					bufForCompareLeft[0] = data[indexArray[gLeft]].dateOfSettling[6];
					bufForCompareLeft[1] = data[indexArray[gLeft]].dateOfSettling[7];
					if (bufForCompareLeft[0] == key[0] && bufForCompareLeft[1] == key[1])
					{
						++amountOfVariants;
						cout << data[indexArray[gLeft]].fullName << " | " << data[indexArray[gLeft]].streetAdress << " | " << data[indexArray[gLeft]].numOfHouse << " \t | " << data[indexArray[gLeft]].numOfFloor << "\t      | " << data[indexArray[gLeft]].dateOfSettling << "      |" << "\n";
						--gLeft;
					}
					else {
						fLeft = false;
					}
				}
				else
				{
					fLeft = false;
				}
			}
			cout << data[indexArray[mid]].fullName << " | " << data[indexArray[mid]].streetAdress << " | " << data[indexArray[mid]].numOfHouse << " \t | " << data[indexArray[mid]].numOfFloor << "\t      | " << data[indexArray[mid]].dateOfSettling << "      |" << "\n";
			bool fRight = true;
			int gRight = mid + 1;
			while (fRight)
			{
				if (gRight < size)
				{
					char bufForCompareRight[2];
					bufForCompareRight[0] = data[indexArray[gRight]].dateOfSettling[6];
					bufForCompareRight[1] = data[indexArray[gRight]].dateOfSettling[7];
					if (bufForCompareRight[0] == key[0] && bufForCompareRight[1] == key[1])
					{
						++amountOfVariants;
						cout << data[indexArray[gRight]].fullName << " | " << data[indexArray[gRight]].streetAdress << " | " << data[indexArray[gRight]].numOfHouse << " \t | " << data[indexArray[gRight]].numOfFloor << "\t      | " << data[indexArray[gRight]].dateOfSettling << "      |" << "\n";
						++gRight;
					}
					else
					{
						fRight = false;
					}
				}
				else
				{
					fRight = false;
				}
			}
			cout << "\n\nWas found " << amountOfVariants << " of variants...\n";
			return;
		}
		if (charToInt(bufForCompare) < charToInt(key))
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

void printRecord(record* Array, int size)
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

void make_binary_b_tree()

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

	cout << "Menu\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records by:\n\t1)Date of settling\n\t2)Name of street\n3)Find a records by key\n0.Exit\n";
	int choose = 0;
	while (cin >> choose)
	{
		cout << "\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records by:\n\t1)Date of settling\n\t2)Name of street\n3)Find a records by key\n0.Exit\n";
		if (choose == 1)
		{
			printRecord(recArray, Size);
		}
		if (choose == 2)
		{
			cout << "\nChoose how u would like to sort this database:\n1 - By date of settling\n2 - By name of the street\nYour choice = ";
			int chooseOrder = 0;
			cin >> chooseOrder; 
			if (chooseOrder == 1)
			{
				indexSort(recArray, indArray, Size, BYDATEOFSETTLING);
			}
			if (chooseOrder == 2)
			{
				indexSort(recArray, indArray, Size, BYSTREETNAME);
			}
			printRecordByIndexArray(indArray, recArray, Size);
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
			indexSort(recArray, bIndArray, Size, BYDATEOFSETTLING);
			findByYearOfSettling(bIndArray, recArray, Size, key);
		}
		if (choose == 0)
		{
			exit(1);
		}
	}
	fclose(file);
}

int main()
{
	menu();
	system("PAUSE");
	return 0;
}