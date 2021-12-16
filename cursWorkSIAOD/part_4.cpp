#include "part_4.h"

double mid_length(std::vector<symb>& c)
{
	float sumLen = 0;
	for (int i = 0; i < c.size(); i++)
		sumLen += c[i].probability * c[i].length_of_code;
	return sumLen;
}

double entropy(std::vector<symb>& c)
{
	float entrop = 0;
	for (int i = 0; i < c.size(); i++)
		entrop += c[i].probability * log2(c[i].probability);
	return -entrop;
}

void sorting(std::vector<symb>& c, int L, int R) {
	int a = c[L].amount_of_uses, i = L, j = R;
	symb t;
	while (i <= j) {
		while (c[i].amount_of_uses > a)i++;
		while (c[j].amount_of_uses < a)j--;
		if (i <= j) {
			t = c[i];
			c[i] = c[j];
			c[j] = t;
			i++;
			j--;
		}
	}
	if (L < j) sorting(c, L, j);
	if (i < R) sorting(c, i, R);
}

int up(int n, double q, std::vector<symb>& c, double* chance)
{
	int i = 0, j = 0;
	for (i = n - 2; i >= 1; --i)
	{
		if (c[i - 1].probability < q)
		{
			c[i].probability = c[i - 1].probability;
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
	c[j].probability = q;
	return j;
}

void down(int n, int j, std::vector<symb>& c)
{
	char p[32];
	for (int i = 0; i < 32; ++i)
	{
		p[i] = c[j].code[i];
	}
	int l = c[j].length_of_code;
	for (int i = j; i < n - 2; ++i)
	{
		for (int k = 0; k < 32; ++k)
		{
			c[i].code[k] = c[i + 1].code[k];
		}
		c[i].length_of_code = c[i + 1].length_of_code;
	}
	for (int i = 0; i < 32; ++i)
	{
		c[n - 2].code[i] = p[i];
		c[n - 1].code[i] = p[i];
	}
	c[n - 1].code[l] = '1';
	c[n - 2].code[l] = '0';
	c[n - 1].length_of_code = l + 1;
	c[n - 2].length_of_code = l + 1;
}

void huffman_coding(int n, double* chance, std::vector<symb>& c)
{
	if (n == 2)
	{
		c[0].code[0] = '0';
		c[1].code[0] = '1';
		c[0].length_of_code = 1;
		c[1].length_of_code = 1;
	}
	else
	{
		double q = chance[n - 2] + chance[n - 1];
		int j = up(n, q, c, chance);
		huffman_coding(n - 1, chance, c);
		down(n, j, c);
	}
}

void decode(ifstream& f)
{
	char ch;
	int amount = 0;
	std::vector<symb> c(256);
	f.seekg(0, std::ios::beg);

	while (f.read(&ch, 1)) {
		c[static_cast<int>(ch) + 128].simbol = ch;
		c[static_cast<int>(ch) + 128].amount_of_uses++;
		amount++;
	}

	for (int i = 0; i < c.size(); i++) {
		if (c[i].amount_of_uses == 0) {
			c.erase(c.begin() + i);
			i--;
		}
		else
			c[i].probability = static_cast<float>(c[i].amount_of_uses) / amount;
	}
	std::cout << "Amount: " << c.size() << "\n\n";

	sorting(c, 0, c.size() - 1);

	double* chance_l = new double[amount];
	for (int i = 0; i < c.size(); ++i)
	{
		chance_l[i] = c[i].probability;
	}


	huffman_coding(c.size(), chance_l, c);


	int count = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	for (int i = 0; i < c.size(); ++i, ++count) {
		if (count < 20)
		{
			if (c[i].simbol != '\r' || c[i].simbol != '\n' || c[i].simbol)
				std::cout << "\t" << i + 1 << ") " << "[" << c[i].simbol << "]" << "\t" << c[i].amount_of_uses << "\t\t" << c[i].probability << "\t\t" << c[i].code << "\n";
		}
		else
		{
			std::cout << "\n Entropy: " << entropy(c) << "\n Medium length: " << mid_length(c) << "\n";
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