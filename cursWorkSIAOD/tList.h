#include <iostream>
#include "tNode.h"

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

