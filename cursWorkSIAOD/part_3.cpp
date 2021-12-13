#include "part_3.h"

int counterp = 0;

int HR, VR;

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


void print_from_left_to_right(Vertex* p, int* indexArray, record* d, Vertex* root) {
	if (p) {
		print_from_left_to_right(p->left, indexArray, d, root);
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
				char ch[9];
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
		print_from_left_to_right(p->right, indexArray, d, root);
	}
}

void find_by_year_of_settling(int* indexArray, record* data, int size, char* key)
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
			print_from_left_to_right(btree, indexArray, data, btree);
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