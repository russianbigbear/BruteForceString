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

/*������� ���������� �������� � �������� ����������*/
void ReadFile() {
	ifstream ifs;
	int size;

	//��������� ���������� � �����
	ifs.open("input.txt");
	ifs >> size; ifs >> _substring;
	for (int i = 0; i < size; i++) {
		_alphabet.push_back(' ');	
		ifs >> _alphabet[i];
	}
	ifs.close();
}

/*������� ��������� ������*/
void CreateText() {
	int sizeT = rand() % 50 + 1; //����� ������

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

/*������� ������ ��������*/
void PrintAlphabet() {
	cout << "��������� �������: ";
	for (int i = 0; i < _alphabet.size(); i++)
		if (_alphabet[i] != ' ')  cout << _alphabet[i] << " ";
		else cout << "_ ";
		cout << endl;
		cout << "������ ����� ��������� - " << _substring << endl;
}

/*�������� ��������� ������� � ���������*/
bool TrueChar(char ch) {
	for (int i = 0; i < _alphabet.size(); i++)
		if (ch == _alphabet[i])
			return true;
		else
			if (ch == _substring)
				return true;
			
	return false;
}

/*���� �������*/
void WriteExample() {
	cout << "������� ������� ��� ������: ";
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

/*�������� ������� ����� ��������� � ����� � ������*/
vector<char> DeleteSub() {
	vector<char> tmp;

	for (int i = 0; i < _example.size(); i++) {
		if (!(_example[i] == '*' && (i == 0 || i == _example.size() - 1)))
			tmp.push_back(_example[i]);
	}

	return tmp;
}


/*�������� ������� ����� ��������� � ��������*/
bool FindSubCenter(vector<char> tmp) {
	for (int i = 0; i < tmp.size(); i++)
		if (tmp[i] == '*') return true;
	return false;
}

/*����� ������� �������*/
vector<pair<int, int>>  BruteForce(vector<char> exmp){
	size_t sizeE = exmp.size();
	size_t sizeT = _text.size();
	vector<pair<int, int>> result;

	for (int i = 0; i < sizeT - sizeE + 1; i++) {
		for (int j = 0; j < sizeE; j++)
			if (exmp[j] != _text[i + j])
				break;
			else if (j == sizeE - 1) {
				result.push_back({i, i + sizeE - 1}); //������� ������� ������ ��������� � �����
				break;
			}
	}

	return result;
}

/*����� ������� ������� ���� � �������� ���� ������ ���������*/
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

/*������ ���������� 1 ������*/
void WriteRes(vector<pair<int,int>> result, int var) {
	ofstream in;

	in.open("result.txt");

	in << "������� �������: ";
	for (int i = 0; i < _example.size(); i++)
		in << _example[i];
	in << endl;

	switch (var){
	case 1: {
		for (int i = 0; i < result.size(); i++) {
			in << i + 1 << " ������� � �������� ������ - " << (result[i].first + 1) << " � ������ - " << (result[i].second + 1) << endl;

			if (result[i].first != 0) {
				in << "����� ����� ����� ������� ������: ";
				for (int j = 0; j < result[i].first; j++)
					if (j + 1 != result[i].first)
						in << j + 1 << ",";
					else
						in << j + 1; 
			}
			in << endl;

			if (result[i].second != _text.size() - 1) {
				in << "����� ����� ����� ������� �����: ";
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
			in << i + 1 << " ������� � �������� ������ - " << (result[i].first + 1) << " � ������ - " << (result[i].second + 1) << endl;

			if (result[i].first != 0) {
				in << "����� ����� ����� ������� ������: ";
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
			in << i + 1 << " ������� � �������� ������ - " << (result[i].first + 1) << " � ������ - " << (result[i].second + 1) << endl;

			if (result[i].second != _text.size() - 1) {
				in << "����� ����� ����� ������� �����: ";
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
			in << i + 1 << " ������� � �������� ������ - " << (result[i].first + 1) << " � ������ - " << (result[i].second + 1) << endl;
		break;
	}
	
	default:
		break;
	}

	in.close();
}

/*���c� ��������� �������*/
void FindExample() {
	vector<pair<int,int>> res;

	//1 ������, ����� *...*
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
		//2 ������, ����� *...
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
			//3 ������, ����� ...*
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
			//������ ����� ��� * � ������ � �����
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

/*�������� �������*/
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));
	remove("text.txt"); remove("result.txt");

	ReadFile();				//������ �������� ����
	CreateText();		    //������������� �����
	PrintAlphabet();		//����� ��������	
	WriteExample();			//���� �������
	FindExample();          //����� �������

	system("pause");
	return 0;
}
