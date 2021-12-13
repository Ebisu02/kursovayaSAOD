#pragma once
#include <string.h>
#include "part_1.h"
#include "part_2.h"

struct Vertex {
	int data;
	int balance;
	Vertex* left, * right;
};

void make_b2tree(int D, Vertex*& p);
void search_in_tree(Vertex* root, char* key, record* data, int* ind);
void print_from_left_to_right(Vertex* p, int* indexArray, record* d, Vertex* root);
void find_by_year_of_settling(int* indexArray, record* data, int size, char* key);

