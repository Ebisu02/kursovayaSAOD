#pragma once
#include "part_1.h"
#include <string>

int char_to_int(char* simbol1);

void make_heap(int arr[], int size, int i, record* data);

void index_sort(record* data, int* arr, int size);

void print_record_by_index_array(int* indexArray, record* recordBuffer, int size);