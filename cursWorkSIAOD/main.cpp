#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "part_1.h"
#include "part_2.h"
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

#include <string.h>

void search_in_tree(Vertex* root, char* key, record* data, int* ind) {
	if (root) {
		if (key[1] < data[ind[root->data]].dateOfSettling[1]) {
			search_in_tree(root->left, key, data, ind);
		}
		else if (key[1] > data[ind[root->data]].dateOfSettling[7]) {
			search_in_tree(root->left, key, data, ind);
		}
		else if (key[1] == data[ind[root->data]].dateOfSettling[1]) {
			search_in_tree(root->left, key, data, ind);
			cout << data[ind[root->data]].fullName << " \t| " << data[ind[root->data]].streetAdress << " \t| " << data[ind[root->data]].numOfHouse << " \t| " << data[ind[root->data]].numOfFloor << " \t| " << data[ind[root->data]].dateOfSettling << "\n";
			search_in_tree(root->left, key, data, ind);
		}
	}
}


void printFromLeftToRight(Vertex* p, int* indexArray, record* d, Vertex* root) {
	if (p) {
		printFromLeftToRight(p->left, indexArray, d, root);
		if (counterp < 20)
		{
			++counterp;
			cout << d[indexArray[p->data]].fullName << " \t| " << d[indexArray[p->data]].streetAdress << " \t| " << d[indexArray[p->data]].numOfHouse << " \t| " << d[indexArray[p->data]].numOfFloor << " \t| " << d[indexArray[p->data]].dateOfSettling << "\n";
		}
		else
		{
			cout << "\nIf u want to find some records by day of settling, then write '2'";
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
			else if (chs == 2)
			{
				char ch[8];
				cout << "\nEnter a date what u wanna find: (format dd-mm-yy)";
				cin >> ch;
				search_in_tree(root, ch, d, indexArray);
			}
			else
			{
				cout << "\nInvalid choice\n";
			}
		}
		c:
		printFromLeftToRight(p->right, indexArray, d, root);
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
			printFromLeftToRight(btree, indexArray, data, btree);
			cout << "\n\nWas found " << amountOfVariants << " of variants...\n";
			queue->clear();
			delete cur;
			delete queue;
			delete btree;
			return;
		}
		if (char_to_int(bufForCompare) < char_to_int(key))
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

struct symb {
	char smb;
	int sum = 0;
	double pr = 0;
	int length = 0;
	char code[32];
};

double midLength(std::vector<symb>& charNumb) {
	float sumLen = 0;
	for (int i = 0; i < charNumb.size(); i++)
		sumLen += charNumb[i].pr * charNumb[i].length;
	return sumLen;
}

double entropy(std::vector<symb>& charNumb) {
	float entrop = -1;
	for (int i = 0; i < charNumb.size(); i++)
		entrop += charNumb[i].pr * log2(charNumb[i].pr);
	return -entrop;
}

void sort1(std::vector<symb>& charNumb, int L, int R) {
	int a = charNumb[L].sum, i = L, j = R;
	symb t;
	while (i <= j) {
		while (charNumb[i].sum > a)i++;
		while (charNumb[j].sum < a)j--;
		if (i <= j) {
			t = charNumb[i];
			charNumb[i] = charNumb[j];
			charNumb[j] = t;
			i++;
			j--;
		}
	}
	if (L < j) sort1(charNumb, L, j);
	if (i < R) sort1(charNumb, i, R);
}

int Up(int n, double q, std::vector<symb>& c, double* chance)
{
	int i = 0, j = 0;
	for (i = n - 2; i >= 1; --i)
	{
		if (c[i - 1].pr < q)
		{
			c[i].pr = c[i - 1].pr;
		}
		else
		{
			j = i;
			break;
		}
		if ((i - 1) == 0 && chance[i - 1] < q)
		{
			j = 0;
			break;
		}
	}
	c[j].pr = q;
	return j;
}

void Down(int n, int j, std::vector<symb>& c)
{
	char p[32];
	for (int i = 0; i < 32; ++i)
	{
		p[i] = c[j].code[i];
	}
	int l = c[j].length;
	for (int i = j; i < n - 2; ++i)
	{
		for (int k = 0; k < 32; ++k)
		{
			c[i].code[k] = c[i + 1].code[k];
		}
		c[i].length = c[i + 1].length;
	}
	for (int i = 0; i < 32; ++i)
	{
		c[n - 2].code[i] = p[i];
		c[n - 1].code[i] = p[i];
	}
	c[n - 1].code[l] = '1';
	c[n - 2].code[l] = '0';
	c[n - 1].length = l + 1;
	c[n - 2].length = l + 1;
}

void huffman(int n, double* chance, std::vector<symb>& c)
{
	if (n == 2)
	{
		c[0].code[0] = '0';
		c[1].code[0] = '1';
		c[0].length = 1;
		c[1].length = 1;
	}
	else
	{
		double q = chance[n - 2] + chance[n - 1];
		int j = Up(n, q, c, chance);
		huffman(n - 1, chance, c);
		Down(n, j, c);
	}
}

void decode(ifstream& f)
{
	char ch;
	int numberOfsymb = 0;
	std::vector<symb> charNumb(256);
	f.seekg(0, std::ios::beg);

	while (f.read(&ch, 1)) {
		charNumb[static_cast<int>(ch) + 128].smb = ch;
		charNumb[static_cast<int>(ch) + 128].sum++;
		numberOfsymb++;
	}

	for (int i = 0; i < charNumb.size(); i++) {
		if (charNumb[i].sum == 0) {
			charNumb.erase(charNumb.begin() + i);
			i--;
		}
		else
			charNumb[i].pr = static_cast<float>(charNumb[i].sum) / numberOfsymb;
	}
	std::cout << "Amount: " << charNumb.size() << "\n\n";

	sort1(charNumb, 0, charNumb.size() - 1);

	double* chance_l = new double[numberOfsymb];
	for (int i = 0; i < charNumb.size(); ++i)
	{
		chance_l[i] = charNumb[i].pr;
	}


	huffman(charNumb.size(), chance_l, charNumb);


	int count = 0;
	for (int i = 0; i < charNumb.size(); ++i, ++count) {
		if (count < 20)
		{
			std::cout << "\t" << i + 1 << ") " << "[" << charNumb[i].smb << "]" << "\t" << charNumb[i].sum << "\t\t" << charNumb[i].pr << "\t\t" << charNumb[i].code << "\n";
		}
		else
		{
			std::cout << "\n Entropy: " << entropy(charNumb) << "\n Medium length: " << midLength(charNumb) << "\n";
			cout << "\nIf u wanna see next page - write '1', if not - write '0'\n";
			int chs = -1;
			cin >> chs;
			if (chs == 0)
			{
				return;
			}
			else if (chs == 1)
			{
				count = 0;
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
			findByYearOfSettling(bIndArray, recArray, Size, key);
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