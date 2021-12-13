#include "part_2.h"

int char_to_int(char* simbol1)
{
	return stoi(simbol1);
}

void make_heap(int arr[], int size, int i, record* data)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;


	char bufForLargestY[2];
	char bufForLargestM[2];
	char bufForLargestD[2];

	bufForLargestY[0] = data[arr[largest]].dateOfSettling[6];
	bufForLargestY[1] = data[arr[largest]].dateOfSettling[7];
	bufForLargestM[0] = data[arr[largest]].dateOfSettling[3];
	bufForLargestM[1] = data[arr[largest]].dateOfSettling[4];
	bufForLargestD[0] = data[arr[largest]].dateOfSettling[0];
	bufForLargestD[1] = data[arr[largest]].dateOfSettling[1];

	long int cLargest = char_to_int(bufForLargestY) * 12 * 30 + char_to_int(bufForLargestM) * 30 + char_to_int(bufForLargestD);


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

		long int cL = char_to_int(bufForLY) * 12 * 30 + char_to_int(bufForLM) * 30 + char_to_int(bufForLD);

		if (cL == cLargest)
		{
			if (l < size && data[arr[l]].streetAdress[0] >= data[arr[largest]].streetAdress[0])
			{
				largest = l;
			}
		}
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

	cLargest = (char_to_int(bufForLargestY) * 12 * 30) + (char_to_int(bufForLargestM) * 30) + char_to_int(bufForLargestD);

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

		long int cR = char_to_int(bufForRY) * 12 * 30 + char_to_int(bufForRM) * 30 + char_to_int(bufForRD);
		if (cR == cLargest)
		{
			if (r < size && data[arr[r]].streetAdress[0] >= data[arr[largest]].streetAdress[0])
			{
				largest = r;
			}
		}
		if (cR > cLargest)
		{
			largest = r;
		}

	}



	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		make_heap(arr, size, largest, data);
	}

}

void index_sort(record* data, int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		make_heap(arr, size, i, data);
	}
	for (int i = size - 1; i >= 0; --i)
	{
		swap(arr[0], arr[i]);
		make_heap(arr, i, 0, data);
	}
}

void print_record_by_index_array(int* indexArray, record* recordBuffer, int size)
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