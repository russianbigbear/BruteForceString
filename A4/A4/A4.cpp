#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
using namespace std;

vector<char> _alphabet;
vector<char> _example;
vector<char> _text;
char _substring;

/*функция считывания алфавита и основной информации*/
void ReadFile() {
	ifstream ifs;
	int size;

	//считываем информацию с файла
	ifs.open("input.txt");
	ifs >> size; ifs >> _substring;
	for (int i = 0; i < size; i++) {
		_alphabet.push_back(' ');	
		ifs >> _alphabet[i];
	}
	ifs.close();
}

/*функция генерации текста*/
void CreateText() {
	int sizeT = rand() % 50 + 1; //рамер текста

	ofstream ofs;
	ofs.open("text.txt");
	for (int j = 0; j < sizeT; j++) {
		char tmp;
		tmp = _alphabet[rand() % _alphabet.size() + 0];
		_text.push_back(tmp);
		ofs << tmp;
	}
	ofs.close();
}

/*функция вывода алфавита*/
void PrintAlphabet() {
	cout << "Доступный алфавит: ";
	for (int i = 0; i < _alphabet.size(); i++)
		if (_alphabet[i] != ' ')  cout << _alphabet[i] << " ";
		else cout << "_ ";
		cout << endl;
		cout << "Символ любой подстроки - " << _substring << endl;
}

/*проверка введнного символа с алфавитом*/
bool TrueChar(char ch) {
	for (int i = 0; i < _alphabet.size(); i++)
		if (ch == _alphabet[i])
			return true;
		else
			if (ch == _substring)
				return true;
			
	return false;
}

/*ввод образца*/
void WriteExample() {
	cout << "Введите образец для поиска: ";
	char ch = ' ';
	do {
		ch = _getch();

		if (ch != 13) {
			if (TrueChar(ch)) {
				putchar(ch);
				_example.push_back(ch);
			}
			else if (ch == 8) {
				printf("\b \b");
				_example.pop_back();
			}
		}	
				
	} while (ch != 13);
	cout << endl;

}

/*удаление символа любой подстроки с конца и начала*/
vector<char> DeleteSub() {
	vector<char> tmp;

	for (int i = 0; i < _example.size(); i++) {
		if (!(_example[i] == '*' && (i == 0 || i == _example.size() - 1)))
			tmp.push_back(_example[i]);
	}

	return tmp;
}


/*проверка символа любой подстроки в середине*/
bool FindSubCenter(vector<char> tmp) {
	for (int i = 0; i < tmp.size(); i++)
		if (tmp[i] == '*') return true;
	return false;
}

/*поиск наивным методом*/
vector<pair<int, int>>  BruteForce(vector<char> exmp){
	size_t sizeE = exmp.size();
	size_t sizeT = _text.size();
	vector<pair<int, int>> result;

	for (int i = 0; i < sizeT - sizeE + 1; i++) {
		for (int j = 0; j < sizeE; j++)
			if (exmp[j] != _text[i + j])
				break;
			else if (j == sizeE - 1) {
				result.push_back({i, i + sizeE - 1}); //заносим индексы начала подстроки и конец
				break;
			}
	}

	return result;
}

/*поиск наивным методом если в середине есть символ подстроки*/
vector<pair<int, int>>  BruteForceMod(vector<char> exmp) {

	vector<pair<int, int>> result;
	vector<char> subF; vector<char> subS;

	int fl = 1;
	for (int i = 0; i < exmp.size(); i++) {
		if (exmp[i] == '*') {
			fl = 2;
			continue;
		}
		if(fl == 1) subF.push_back(exmp[i]);
		else subS.push_back(exmp[i]);
	}

	vector<pair<int, int>> rF = BruteForce(subF);
	vector<pair<int, int>> rS = BruteForce(subS);

	for (int i = 0; i < rF.size(); i++) {
		for (int j = 0; j < rS.size(); j++) {
			if (rF[i].second <= rS[j].first)
				result.push_back({ rF[i].first, rS[j].second });
		}
	}

	return result;
}

/*запись результата 1 случай*/
void WriteRes(vector<pair<int,int>> result, int var) {
	ofstream in;

	in.open("result.txt");

	in << "Искомый образец: ";
	for (int i = 0; i < _example.size(); i++)
		in << _example[i];
	in << endl;

	switch (var){
	case 1: {
		for (int i = 0; i < result.size(); i++) {
			in << i + 1 << " образец с индексом начала - " << (result[i].first + 1) << " и концом - " << (result[i].second + 1) << endl;

			if (result[i].first != 0) {
				in << "может также иметь индексы начала: ";
				for (int j = 0; j < result[i].first; j++)
					if (j + 1 != result[i].first)
						in << j + 1 << ",";
					else
						in << j + 1; 
			}
			in << endl;

			if (result[i].second != _text.size() - 1) {
				in << "может также иметь индексы конца: ";
				for (int j = result[i].second; j < _text.size(); j++)
					if (j + 1 != _text.size())
						in << j + 1 << ",";
					else
						in << j + 1;
			}
			in << endl;
		}
		break;
	}
	case 2: {
		for (int i = 0; i < result.size(); i++) {
			in << i + 1 << " образец с индексом начала - " << (result[i].first + 1) << " и концом - " << (result[i].second + 1) << endl;

			if (result[i].first != 0) {
				in << "может также иметь индексы начала: ";
				for (int j = 0; j < result[i].first; j++)
					if (j + 1 != result[i].first)
						in << j + 1 << ",";
					else
						in << j + 1;
			}
			in << endl;
		}
		break;
	}
	case 3: {
		for (int i = 0; i < result.size(); i++) {
			in << i + 1 << " образец с индексом начала - " << (result[i].first + 1) << " и концом - " << (result[i].second + 1) << endl;

			if (result[i].second != _text.size() - 1) {
				in << "может также иметь индексы конца: ";
				for (int j = result[i].second; j < _text.size(); j++)
					if (j + 1 != _text.size())
						in << j + 1 << ",";
					else
						in << j + 1;
			}
			in << endl;
		}
		break;
	}
	case 4: {
		for (int i = 0; i < result.size(); i++) 
			in << i + 1 << " образец с индексом начала - " << (result[i].first + 1) << " и концом - " << (result[i].second + 1) << endl;
		break;
	}
	
	default:
		break;
	}

	in.close();
}

/*поиcк заданного образца*/
void FindExample() {
	vector<pair<int,int>> res;

	//1 случай, когда *...*
	if (_example[0] == '*' && _example[_example.size() - 1] == '*') {
		vector<char> tmp = DeleteSub();
		
		if (!FindSubCenter(tmp)) {
			res = BruteForce(tmp);
			WriteRes(res,1);
		}
		else {
			res = BruteForceMod(tmp);
			WriteRes(res,1);
		}
	}
	else
		//2 случай, когда *...
		if (_example[0] == '*') {
			vector<char> tmp = DeleteSub();

			if (!FindSubCenter(tmp)) {
				res = BruteForce(tmp);
				WriteRes(res, 2);
			}
			else {
				res = BruteForceMod(tmp);
				WriteRes(res, 2);
			}

		}
		else
			//3 случай, когда ...*
			if (_example[_example.size() - 1] == '*') {
				vector<char> tmp = DeleteSub();

				if (!FindSubCenter(tmp)) {
					res = BruteForce(tmp);
					WriteRes(res, 3);
				}
				else {
					res = BruteForceMod(tmp);
					WriteRes(res, 3);
				}
			}
			//случай когда нет * в начале и конце
			else {
				vector<char> tmp = DeleteSub();

				if (!FindSubCenter(tmp)) {
					res = BruteForce(tmp);
					WriteRes(res, 4);
				}
				else {
					res = BruteForceMod(tmp);
					WriteRes(res, 4);
				}
			}
}

/*основная функция*/
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));
	remove("text.txt"); remove("result.txt");

	ReadFile();				//чтение основной инфо
	CreateText();		    //сгенерировали текст
	PrintAlphabet();		//вывод алфавита	
	WriteExample();			//ввод образца
	FindExample();          //поиск образца

	system("pause");
	return 0;
}
