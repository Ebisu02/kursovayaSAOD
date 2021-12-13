#pragma once
#include "part_1.h"
#include <vector>
#include <fstream>

struct symb {
	char simbol;
	int amount_of_uses = 0;
	double probability = 0;
	int length_of_code = 0;
	char code[32];
};

double mid_length(std::vector<symb>& charNumb);
double entropy(std::vector<symb>& charNumb);
int up(int n, double q, std::vector<symb>& c, double* chance);
void down(int n, int j, std::vector<symb>& c);
void huffman_coding(int n, double* chance, std::vector<symb>& c);
void decode(ifstream& f);