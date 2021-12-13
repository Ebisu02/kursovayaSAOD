#include <iostream>

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

