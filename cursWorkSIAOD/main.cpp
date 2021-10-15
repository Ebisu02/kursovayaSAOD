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

int main()
{
	FILE* fileOut;
	int tSize = 120;
	fopen_s(&fileOut, Path, "rb");
	record recordBuffer[Size] = { 0 };
	int counter = 0;
	counter = fread((record*)recordBuffer, sizeof(record), Size, fileOut);
	for (int i = 0; i < tSize; ++i)
	{
		cout << recordBuffer[i].fullName << " | " << recordBuffer[i].streetAdress << " | " << recordBuffer[i].numOfHouse << " | " << recordBuffer[i].numOfFloor << " | " << recordBuffer[i].dateOfSettling << "\n";
	}
	fclose(fileOut);

	cout << "\n\n";

	int* indexArray = new int[tSize];
	for (int i = 0; i < tSize; ++i)
	{
		indexArray[i] = i;
	}
	indexSort(recordBuffer, indexArray, tSize, BYDATEOFSETTLING);
	printRecordByIndexArray(indexArray, tSize);

	char buf[2];

	buf[0] = '9';
	buf[1] = '5';

	findByYearOfSettling(indexArray, recordBuffer, tSize, buf);

	delete[] indexArray;

	system("PAUSE");
	return 0;
}