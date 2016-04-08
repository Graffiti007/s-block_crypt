#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>

// ���������� �Ѩ!

#include "Sfiles.h"// ��� ��� ������-����� �� �����

using namespace std;

map <int, int> swap(map <int, int> tabl, int count);// ������������ ������� ������.
map <int, int> generate_tabl(int count);// ������� ������� ������ ������ n*m - 2. ���������� �� ����� xor � ������. ������� ��� �� ����������, ������ � swap
vector <int> generate_key(int n, int m, int j);// ������� ���� ������� n*m*j. ���� ��� �� ������
vector < vector <int> > sub(vector<int> key, int n, int m, int j);// ��������� ���� �� k(i)
int Counter_Bits(vector <string> &text); // ������� ����� � ������
map <string, string> generate_sbox(int m); // ������� ������� ������� (2^m - 2). � ��� ��� �� ������� ���������� ����������� 000, 001... (������ ������ Random_sbox)
string Random_Bytes(int m); // ��������� ��������� ������������������ 0 � 1 ����� m
vector <string> Random_sbox(int m); // ��������� s-blokov, ������, �� �� ������������, ����� ������� � map � ������ sbox
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // ��������� ������� ����������� sbox

int main()
{
	srand(time(0));

	map <string, string> sbox = generate_sbox(3);
	map <string, string> table = generate_tabl_mix(sbox, 3);

	for (auto e : table)
	{
		cout << e.first << " " << e.second << endl;
	}

	return 0;
}

map <int, int> swap(map <int, int> tabl, int count)
{
	for (int i = 0; i<count; i++)
		swap(tabl[i], tabl[rand() % count]);// ���������� ������� ������
	return tabl;
}

map <int, int> generate_tabl(int count)
{
	map <int, int> a;
	for (int i = 0; i<count; i++)
		a[i] = i;
	return a;
}

vector <int> generate_key(int n, int m, int j)
{
	vector <int> key;
	int r;
	for (int i = 0; i<n*m*j; i++) //���������� ����
	{
		r = rand() % 2; //���������� ������������� �����, ����� ������� �� ������� �� 2 (�� ����� ��� ���)
		key.push_back(r);// ���������� � ������
	}
	return key;
}

vector <vector<int>> sub(vector<int> key, int n, int m, int j)
{
	vector <vector <int>> sub_key;
	int counter = 0;

	sub_key.resize(j); // ��� ����� �� �������� (??!??!!!)
	for (int i = 0; i<n; i++)// � ����� �� 1 �� n (n ����)
	{
		sub_key[i].resize(n*m);
		for (int k = 0; k<n*m; k++) // � ����� �� 1 �� m (������ m)
		{
			sub_key[i].push_back(key[counter]);
			counter++;
		}
	}
	return sub_key;
}

int Counter_Bits(vector <string> &text)
{
	int count = 0;
	for (int i = 0; i < (int)text.size(); i++)
	{
		for (int j = 0; j < (int)text[i].size(); j++)
		{
			unsigned int temp = text[i][j];
			while (temp != 0)
			{
				temp = temp >> 1;
				count++;
			}
		}
	}
	return count;
}

string Random_Bytes(int m)
{
	string str;
	for (int i = 0; i < m; i++)
	{
		char temp = rand() % 2 + '0';
		str = str + temp;
	}
	return str;
}

vector <string> Random_sbox(int m)
{
	vector <string> temp_table;

	for (int i = 0; i < (int)pow(2.0, (double)m); i++)
	{
		int k = i;
		string str;
		for (int j = 0; j < m; j++)
		{
			char temp = k % 2 + '0';
			str = str + temp;
			k = k / 2;
		}

		temp_table.push_back(str);
	}
	random_shuffle(begin(temp_table), end(temp_table));
	return temp_table;
}

map <string, string> generate_sbox(int m)
{
	map <string, string> table;
	int k;

	for (int i = 0; i < (int) pow(2.0, (double) m); i++)
	{
		k = i;
		string str;
		for (int j = 0; j < m; j++)
		{
			char temp = k % 2 + '0';
			str = str + temp;
			k = k / 2;
		}
		table[str] = str;
	}
	return table;
}

map <string, string> generate_tabl_mix (map <string, string> sblock, int m)
{
	vector <string> temp = Random_sbox(m);
	int i = 0;
	for (auto e : sblock)
	{
		sblock[e.first] = temp[i];
		i++;
	}
	return sblock;
}