#pragma once
#include "tList.h"
#include <iostream>

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

