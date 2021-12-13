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
#include "part_3.h"

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
			find_by_year_of_settling(bIndArray, recArray, Size, key);
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