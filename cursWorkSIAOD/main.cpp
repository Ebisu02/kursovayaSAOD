#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char Path[] = "../testBase4.dat";
const int Size = 4000;

// k = god poseleniya

class tNode

{
public:
	int data;
	tNode* next;

	tNode() :data()
	{
		next = NULL;
	}

	tNode(int value)
	{
		data = value;
		next = NULL;
	}

	tNode(int value, tNode* next_pointer)
	{
		data = value;
		next = next_pointer;
	}
};

class tList
{
protected:
	static int count;

public:
	tNode* head;
	tList()
	{
		head = NULL;
		count++;
	}

	virtual void push() = 0;
	virtual void push(int value) = 0;
	virtual void push(int value, tNode* next_pointer) = 0;
	virtual void clear() = 0;

	void deleteHead()
	{
		try
		{
			if (head == NULL) throw "Nothing to delete";

			tNode* p = head->next;
			delete head;
			head = p;
		}
		catch (const char* exception)
		{
			cerr << "Error: " << exception << '\n';
		}
	};
	void print()
	{
		try
		{
			if (head == NULL) throw "Nothing to print";
			tNode* pos = head;

			while (pos != NULL)
			{
				cout << pos->data << " ";
				pos = pos->next;
			}
			cout << "\n";
		}
		catch (const char* exception)
		{
			cerr << "Error: " << exception << '\n';
		}
	};
	int getCount()
	{
		return count;
	};
};

int tList::count = 0;

class tQueue : public tList
{
protected:
	tNode* tail;

public:
	tQueue()
	{
		tail = (tNode*)&head;
	}

	~tQueue()
	{
		if (head != NULL) clear();
		count--;
	}

	virtual void push()
	{
		tNode* p = new tNode();

		if (head != NULL)
		{
			tail->next = p;
		}
		else
		{
			head = p;
		}

		tail = p;
	};
	virtual void push(int value)
	{
		tNode* p = new tNode(value);

		if (head != NULL)
		{
			tail->next = p;
		}
		else
		{
			head = p;
		}

		tail = p;
	};
	virtual void push(int value, tNode* next_pointer)
	{
		tNode* p = new tNode(value);

		if (head != NULL)
		{
			tail->next = p;
		}
		else
		{
			head = p;
		}

		tail = p;

		p = next_pointer;
		tail->next = p;
		tail = p;
	};
	virtual void clear()
	{
		try
		{
			if (head == NULL) throw "Nothing to free";

			tNode* pos, * q;
			q = pos = head;

			while (pos != NULL)
			{
				pos = q->next;
				delete q;
				q = pos;
			}

			head = NULL;
			tail = NULL;
		}
		catch (const char* exception)
		{
			cerr << "Error: " << exception << '\n';
		}
	};
};

// bd - nas punkt
struct record
{
	char fullName[32]; // <Surname>_<Name>_<Ot4estvo> // Primer - Ïåòpîâ_Èâàí_Ôåäîpîâè÷___________ 
	char streetAdress[18]; // Primer - Ëåíèíà______________
	short int numOfHouse; // nomer doma
	short int numOfFloor; // nomer kvartiri
	char dateOfSettling[10]; // data zaseleniya // Primer - 29-02-65 // Format: dd-mm-yy
};

// ×åñòíî - õåð çíàåò çà÷åì ÿ ýòî âûñðàë, ïûòàëñÿ êàê-òî ñðàâíèòü äàòó â ôîðìàòå dd-mm-yy ïîëíîñòüþ
// Íî ïîêà ÷òî çàáèë õåð, ò.ê. ñèëüíî âëèÿåò íà òðóäîåìêîñòü è âðåìÿ è ñêîðîñòü è âîîáùå... Åáàë ÿ â ðîò ýòî íà ïëþñàõ äåëàòü!
int charToInt(char* simbol1)
{
	return stoi(simbol1);
}

// Òîæå ñîðòèðîâêà, à èìåííî ôîðìèðîâàíèå êó÷è... Áûëî ëåíü äåëàòü 2 îòäåëüíûå äëÿ 2 ðàçíûõ ñëó÷àåâ, ïîýòîìó ñäåëàë ñëîâàðü
// Äëÿ äàííîé ñèòó¸âèíû, î÷åíü ëåíèâûé ÿ, óæ èçâèíèòå, çíàþ, ÷òî ýòî ïëîõîé òîí =)
void makeHeap(int arr[], int size, int i, record* data)
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
		makeHeap(arr, size, largest, data);
	}

}

// Ñîðòèðîâêà, ïèðàìèäàëüíàÿ, íå ïîäõîäèò îíà òóò âîîáùå... Íî... Òàêîå çàäàíèå =)
void indexSort(record* data, int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		makeHeap(arr, size, i, data);
	}
	for (int i = size - 1; i >= 0; --i)
	{
		swap(arr[0], arr[i]);
		makeHeap(arr, i, 0, data);
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

struct Vertex {
	int data;
	int balance;
	Vertex* left, * right;
};

int VR, HR;

void make_b2tree(int D, Vertex*& p)
{
	if (!p)
	{
		p = new Vertex;
		p->data = D;
		p->left = p->right = NULL;
		p->balance = 0;
		VR = 1;
	}
	else if (p->data > D)
	{
		make_b2tree(D, p->left);
		if (VR == 1)
		{
			if (p->balance == 0)
			{
				Vertex* q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				p->balance = 1;
				VR = 0;
				HR = 1;
			}
			else
			{
				p->balance = 0;
				VR = 1;
				HR = 0;
			}
		}
		else
			HR = 0;
	}
	else if (p->data < D)
	{
		make_b2tree(D, p->right);
		if (VR == 1)
		{
			p->balance = 1;
			HR = 1;
			VR = 0;
		}
		else if (HR == 1)
		{
			if (p->balance == 1)
			{
				Vertex* q = p->right;
				p->right = q->left;
				p->balance = 0;
				q->balance = 0;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else
			{
				HR = 0;
			}
		}
	}
}

int counterp = 0;

void printFromLeftToRight(Vertex* p, int* indexArray, record* d) {
	
	if (p) {
		printFromLeftToRight(p->left, indexArray, d);
		if (counterp < 20)
		{
			++counterp;
			cout << d[indexArray[p->data]].fullName << " \t| " << d[indexArray[p->data]].streetAdress << " \t| " << d[indexArray[p->data]].numOfHouse << " \t| " << d[indexArray[p->data]].numOfFloor << " \t| " << d[indexArray[p->data]].dateOfSettling << "\n";
		}
		else
		{
			cout << "\nIf u wanna see next page - write '1', if not - write '0'\n";
			int chs = -1;
			cin >> chs;
			if (chs == 0)
			{
				exit(0);
			}
			else if (chs == 1)
			{
				counterp = 0;
				goto c;
			}
			else
			{
				cout << "\nInvalid choice\n";
			}
		}
		c:
		printFromLeftToRight(p->right, indexArray, d);
	}
}

void findByYearOfSettling(int* indexArray, record* data, int size, char* key)
{
	int left = 0;
	int right = size;
	int counter = 0;
	int amountOfVariants = 0;
	tQueue* queue = new tQueue();
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
						queue->push(gLeft);
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
			++counter;
			queue->push(mid);
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
						queue->push(gRight);
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
			Vertex* btree = nullptr;
			tNode* cur = queue->head;
			while (cur->next)
			{
				make_b2tree(cur->data, btree);
				cur = cur->next;
			}
			printFromLeftToRight(btree, indexArray, data);
			cout << "\n\nWas found " << amountOfVariants << " of variants...\n";
			queue->clear();
			delete cur;
			delete queue;
			delete btree;
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

	cout << "Menu\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records\n3.Find a records by key\n0.Exit\n";
	int choose = 0;
	while (cin >> choose)
	{
		cout << "\n\nWrite a number of point what u want to use\n1.Print records\n2.Print sorted records\n3.Find a records by key\n0.Exit\n";
		if (choose == 1)
		{
			printRecord(recArray, Size);
		}
		if (choose == 2)
		{
			indexSort(recArray, indArray, Size);
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
			indexSort(recArray, bIndArray, Size);
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