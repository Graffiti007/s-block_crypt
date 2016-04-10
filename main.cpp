#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

/*
map <int, int> generate_tabl(int n, int m);//Cоздает таблицу замены размер n*m - 2. Используем во время xor с ключом. Таблица еще не перемешана, мешаем в swap
map <int, int> swap(map <int, int> tabl, int n, int m);//Перемешивает таблицу замены.
vector <int> generate_key(int n, int m, int j);//Cоздает ключ размера n*m*j. Ключ еще не разбит на K(i)
vector < vector <int> > sub(vector<int> key, int n, int m, int j); //Разбиваем ключ на K(i)
int Counter_Bits(vector <string> &text); //Подсчет битов в тексте
string Random_Bytes(int m); //Генерация случайной последовательности 0 и 1 длины m

map <string, string> generate_sbox(int m); //Создает таблицу размера (2^m - 2). В ней как по таблице истинность упорядочены 000, 001... (смотри дальше Random_sbox)
vector <string> Random_sbox(int m); //Генерация s-блока, причем, мы их перемешиваем, после запишем в map и полчим sbox (смотри generate_tabl_mix )
map <string, string> generate_tabl_mix(map <string, string> sblock, int m); // Генерация таблицы подстановки sbox

string generate_text (int n, int m); //Создано для тестов. Генерирует строку n*m из 0 и 1. По сути - открытый текст
vector <vector <string>> sub_str_blok (string text, int n, int m);//Разбивает текст на кучу блоков для дальнейшей замены (покачто хрен знает сколько блоков, размера m, ибо генерируем текст n*m - переполнения не будет)
vector <vector <string>> use_s_box (vector <vector <string>> hs, map <string,string> s_box)

string XOR (vector <vector <string>> hs, map<int,int> p_box, vector< vector<int>> sub_key, int j);//собственно последние два блока, как я понял. XOR, согласно p_box
*/

#include "Sfiles.h"// Работа с файлами
#include "fun.h" // Все остальные функции

int main()
{
	srand(time(0));

	int n, m, j; // Кол-во блоков, размер блока, количество раундов
	vector <int> key; // Ключ
	vector <vector <int>> sub_key; // Разбитый ключ
	map <string,string> sbox; // s-блок
	map<int,int> p_box; // таблица замены, она же функция подстановки (перед XOR)
	string text; // Исходный текст
	vector <vector <string>> hs; // Разбитый на части исходный текст
	string new_text; // Зашифрованный текст
	
	cin >> n >> m >> j;
	
	key = generate_key(n, m, j); // Генерация ключа
	sub_key = sub(key,n,m,j); // Разбиение ключа
	
	
	sbox = generate_sbox(m); // Генерация s-блока
	sbox = generate_tabl_mix(sbox,m); // Перемешивание элементов в таблице

	p_box = generate_tabl(n,m); // Генерация p-блока
	p_box = swap(p_box,n,m); // Перемешивание элементов в таблице

	text = generate_text (n,m); // Генерация текста (тестовая функция)
	hs = sub_str_blok(text,n,m); // Разбиение текста 
	hs = use_s_box(hs,sbox); // Замена битов в тексте в соотвествии с таблицей замены
	new_text = XOR(hs,p_box, sub_key,j); // Сложение по модулю 2 текста и ключа в соотвествии с p-блоком

	return 0;
}
