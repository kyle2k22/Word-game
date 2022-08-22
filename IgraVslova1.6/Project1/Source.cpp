#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

map<int, vector<string>> DICTIONARY;
const char ALPHABET[30] = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' };

void RussianLocalization() {
	SetConsoleCP(1251); // ���� � ������� � ��������� 1251
	SetConsoleOutputCP(1251);// ����� �� ������� � ��������� 1251. ����� ������ ����� �������� ����� ������� �� Lucida Console ��� Consolas
	setlocale(LC_ALL, "rus");
}
void DictionaryFullnessOutput() {
	for (int i = 0; i < 30; i++) {
		for (auto now : DICTIONARY[i]) {
			cout << now << " ";
		}
		cout << endl;
		cout << "==================================================================================================" << endl;
		cout << "������ ���� � ������" << i << endl;
		cout << endl;
		cout << endl;
	}
}
void PrintGameRules()
{
	cout << "����� ����������! ���� �������������� ��� � ����� ����." << endl;
	cout << "���� ���� ����������� � ���, ����� ��������� ����� ����� ,���������� �� �����, ������� ������������� ���������� ����� ���������." << endl;
	cout << "���� ���������� ����� ������������� �� ����� �,�,�, �� ���� �����, ������� ����� ����." << endl;
	cout << "� ������ ���� �� ������ ������� ������� ���������, � ����������� �� ���� � ��� ����� ����������� �� ������� �� ������ ����� �����: " << endl;
	cout << "1 - ������� (30 ������ �� �����)." << endl;
	cout << "2 - ����������� (20 ������ �� �����)." << endl;
	cout << "3 - ����� (10 ������ �� �����)." << endl;
	cout << "���� �� �� ������ ��������� �� �����, �� �� ������� ���������." << endl;
	cout << "� ��� ����� ���� ����������� ������� ������� �����: ���� � ����������� ��� ������� ������ ��������. " << endl;
	cout << "� ����� ���� ��������� ������� ��������, ������� ����� ������������ ��� ������� ����� � ����� �������." << endl;
	cout << "������� ��������:" << endl;
	cout << "1. ����� ����������� �� ������ ���������� �����." << endl;
	cout << "2. ���-�� ����������� ������ ������� �� ��������� ��������� (1 ���� �� ��������� '�������' , 2 ����� �� '�����������', 3 ����� �� '�����')." << endl;
	cout << "� ����� ���� �� ������� ������� ���� ���������, � ����� ��� ����������� ������ � ���� ����." << endl;
	cout << "� ���� ���� ����� ��������� �������� �� ������������(�� ���� ���� ����� ��� ��������� ���� ������,�� ��������� ��������� ������ ������ �����" << endl;
	cout << "� ������ ���� �� ���������, �� ������� ���� ���������� �� ������ ���� ����� � ������� ��� ����������. (���� � �������� ����� � ��� ��� ����������,�� �� ������ ���� ��������� ����,��������� ���� ���������,���� ������� �� ���������, ����� ������� ������)" << endl;
	cout << "���� �� �� ������ �������� �� ������������ ���-�� ����, �� �� ������������." << endl;
	cout << "��� ��� �������, ������� ��� ������� �����.����������� �� ���������� � ��������� ����." << endl;
	cout << "�����!!!" << endl;
}
int Hardness_choose() {
	cout << "�������� ������� ���������:" << endl;
	cout << "1 - <<�������>>" << endl;
	cout << "2 - <<���-�� �������>>" << endl;
	cout << "3 - <<�����>>" << endl;
	int x;
	cin >> x;
	if (x == 1) return 1;
	if (x == 2) return 2;
	if (x == 3) return 3;
}
string WaitAnswer(long long wait)
{
	string answer;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	time_t deadline = time(0) + wait; //��������� ������, ������� ���� �� ������������ ��������(������� �� ��������� ���������) � 0

	while (wait > 0)
	{
		if (WaitForSingleObject(handle, wait * 1000) == WAIT_OBJECT_0)
		{
			if (_kbhit())
			{
				char ch = _getch();
				if (ch >= '�' && ch <= '�') // ��������, ��� ������ �������� ������ - ��� �����
				{
					_putch(ch);

					answer.push_back(ch);
				}
				else if (ch == '\b')
				{
					if (!answer.empty())
					{
						_putch(ch);
						_putch(' ');
						_putch(ch);

						answer.pop_back();
					}
				}
				else if (ch == '\r')
				{
					if (!answer.empty())
						break;
				}
			}
		}
		wait = deadline - time(0); //������ ������ ����� �������� ��������� �� ���������� �����
	}

	_putch('\n');
	_putch('\r');

	return answer;
}
int naib; // ������������ �����, ������� ��� ��������� � ������� ������� ������
int naib1; // ������������ ������, ��������������� �� �����
int MaxRecordInput() {
	ifstream file1;
	file1.open("MaxRecord.txt");
	if (file1.is_open()) {
		file1 >> naib1;
		file1.close();
		return 0;
	}
}
int MaxRecordOutput() {
	ofstream file1;
	file1.open("MaxRecord.txt");
	if (naib >= naib1) file1 << naib;
	else file1 << naib1;
	file1.close();
	return 0;
}
void PvP() {
	string proverka;
	vector <string> unic = {};
	string s1; // ������ �����
	string s2; // ������ �����
	int h = Hardness_choose();
	int brik = 0;
	cout << "���� ��������!" << endl;
	while (true) {

		cout << "��� 1 ������: ";
		if (h == 1) s1 = WaitAnswer(30);
		if (h == 2) s1 = WaitAnswer(20);
		if (h == 3) s1 = WaitAnswer(10);
		if (s1.empty())
		{
			cout << "����� �������! ������ ����� ��������.";
			break;
		}
		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s1) {
				cout << "��������� ����� �� ������ �������� �� ������������! ������� ������: ";
				brik = 1;
			}
		}
		if (brik == 1) {
			if (h == 1) s1 = WaitAnswer(30);
			if (h == 2) s1 = WaitAnswer(20);
			if (h == 3) s1 = WaitAnswer(10);
		}
		unic.push_back(s1);
		if (s1[s1.length() - 1] == '�' or s1[s1.length() - 1] == '�' or s1[s1.length() - 1] == '�') {
			s1.resize(s1.length() - 1); // ������� ��������� ����� �����, ���� ��� �������� �� �������
		}

		cout << "��� 2 ������: ";
		if (h == 1) s2 = WaitAnswer(30);
		if (h == 2) s2 = WaitAnswer(20);
		if (h == 3) s2 = WaitAnswer(10);
		if (s2.empty())
		{
			cout << "����� �������! ������ ����� ��������.";
			break;
		}
		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s2) {
				cout << "��������� ����� �� ������ �������� �� ������������! ������� ������: ";
				brik = 1;
			}
		}
		if (brik == 1) {
			if (h == 1) s2 = WaitAnswer(30);
			if (h == 2) s2 = WaitAnswer(20);
			if (h == 3) s2 = WaitAnswer(10);
		}
		unic.push_back(s2);
		if ((s1[s1.length() - 1] != s2[0]) or s1 == s2) {
			cout << "����� 2 ��������, ����� 1 �������!";
			break;
		}
		if (s2[s2.length() - 1] == '�' or s2[s2.length() - 1] == '�' or s2[s2.length() - 1] == '�') {
			s2.resize(s2.length() - 1); // ������� ��������� ����� �����, ���� ��� �������� �� �������
		}
	}
	cout << endl;
	cout << "=====================================================================================================================" << endl;
}
void RandomWordsInputAndOutput() {
	int h = Hardness_choose();
	string proverka;
	string s1; // ������ ��� ����� ����� �������������
	time_t time_dedline;
	vector <string> unic = {};
	int k = 0, g = 0, random_num_in_array, x = 0, w, brik = 0;
	srand(time(0)); // �������� ��������� ����� ��� ����, ����� ��������� ������ ���� ����� ������ �� ��� �����
	random_num_in_array = rand() % 29;
	while (true) {
		if (proverka.empty() == 1) {
			for (int i = 0; i < 30; i++) {
				if (i == random_num_in_array) {
					for (auto now : DICTIONARY[i]) k++;
					random_num_in_array = rand() % k;
					cout << "������� ������� ����� �� ������ ������������ ������ ����������: ";
					cin >> w;
					w *= 60;
					cout << random_num_in_array << " - ��������� ��������� ����� �� ��������� " << k << " � ������ ����, ������������ �� ���� " << ALPHABET[i] << ": " << endl;
					for (string now : DICTIONARY[i]) {
						g++;
						if (g == random_num_in_array) {
							cout << "���� ��������! ������� ����� � ����� �� <<" << now << ">> : ";
							time_dedline = time(0) + w;
							proverka = now;
							unic.push_back(proverka);
							if (proverka[proverka.length() - 1] == '�' or proverka[proverka.length() - 1] == '�' or proverka[proverka.length() - 1] == '�') {
								proverka.resize(proverka.length() - 1); // ������� ��������� ����� �����, ���� ��� �������� �� �������
							}
						}
					}
				}
			}
			k = 0;
			g = 0;
		}
		if (h == 1) s1 = WaitAnswer(30);
		if (h == 2) s1 = WaitAnswer(20);
		if (h == 3) s1 = WaitAnswer(10);

		if (s1.empty())
		{
			cout << "�����, ������ �� ���� �����, �������! �� ���������. ���������� ��� ���.";
			break;
		}

		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s1) {
				cout << "��������� ����� �� ������ �������� �� ������������! ������� ������: ";
				brik = 1;
			}
		}
		if (brik == 1) {
			if (h == 1) s1 = WaitAnswer(30);
			if (h == 2) s1 = WaitAnswer(20);
			if (h == 3) s1 = WaitAnswer(10);
		}
		unic.push_back(s1);

		if (s1[s1.length() - 1] == '�' or s1[s1.length() - 1] == '�' or s1[s1.length() - 1] == '�') {
			s1.resize(s1.length() - 1); // ������� ��������� ����� �����, ���� ��� �������� �� �������
		}

		if ((proverka.empty() == 0 and (proverka[proverka.length() - 1] != s1[0])) or s1 == proverka) {
			if (h * x > naib) naib = h * x;
			cout << "�� ���������!" << endl;
			cout << "���� ���������� �������: " << x << endl;
			cout << "��� �������: " << h * x << endl;
			if (naib >= naib1) cout << "������ �������: " << naib;
			if (naib < naib1) cout << "������ �������: " << naib1;
			break;
		}
		x++;
		w = time_dedline - time(0);
		if (w <= 0) {
			if (h * x > naib) naib = h * x;
			cout << "����� ����! ���� ���������� �������: " << x << endl;
			cout << "��� �������: " << h * x << endl;
			if (naib >= naib1) cout << "������ �������: " << naib;
			if (naib < naib1) cout << "������ �������: " << naib1;
			break;
		}
		cout << "��������� ����� � ��������� �����: " << s1[s1.length() - 1] << endl;

		for (int i = 0; i < 30; i++) {
			if (s1[s1.length() - 1] == ALPHABET[i]) {
				for (auto now : DICTIONARY[i]) k++;
				srand(time(0));
				random_num_in_array = rand() % k;
				cout << random_num_in_array << " - ��������� ��������� ����� �� ��������� " << k << " � ������ ����, ������������ �� ���� " << ALPHABET[i] << ":" << endl;
				for (string now : DICTIONARY[i]) {
					g++;
					if (g == random_num_in_array) {
						proverka = now; // ���������� �����, ������� ������� ���������, ��� ���������� �������� �� ������������ ���������� ������� ����
						if (proverka[proverka.length() - 1] == '�' or proverka[proverka.length() - 1] == '�' or proverka[proverka.length() - 1] == '�') {
							proverka.resize(proverka.length() - 1); // ������� ��������� ����� �����, ���� ��� �������� �� �������
						}
						cout << now << endl;
						cout << "��� ����������� ���� ������� ����� �����: ";
						break;
					}
					proverka = now;
				}
			}
		}
		k = 0;
		g = 0;
	}
	MaxRecordOutput();
	cout << endl;
	cout << "=====================================================================================================================" << endl;
}
void Play()
{
	cout << "������ ����?" << endl;

	while (true)
	{
		cout << "\t<<�>> - �������� ������� ����" << endl;
		cout << "\t<<�>> - ������ � �����������" << endl;
		cout << "\t<<�>> - ������ � ���������" << endl;
		cout << "\t<<�>> - ���������" << endl;

		char action;
		cin >> action;

		if (action == '�')
		{
			RandomWordsInputAndOutput();
		}
		else if (action == '�')
		{
			PvP();
		}
		else if (action == '�')
		{
			PrintGameRules();
		}
		if (action == '�')
		{
			break;
		}

		cout << "���������?" << endl;
	}
}
bool LoadDictionary()
{
	string s; // ������, � ������� ����� ����������� ���������� ���� �� �����
	ifstream file;
	// ��������� ���� � ��������� ������ �� ��
	file.open("RussianDict.txt");
	if (file.is_open())
	{
		cout << "���� ������" << endl;

		// ������ ���������� �������. ������ ���� i ������������� �������� � ����� �� �������� � ������� Alphabet
		while (!file.eof()) {
			file >> s;
			for (int i = 0; i < 30; i++) {
				if (s[0] == ALPHABET[i]) {
					DICTIONARY[i].push_back(s);
				}
			}
		}
		file.close();
		// ����� ���������� �������
		return true;
	}

	cout << "���� �� ������, �������� ���� ������ �������!" << endl;
	return false;
}
int main()
{
	RussianLocalization();
	if (LoadDictionary())
	{
		MaxRecordInput();
		Play();
	}
	return 0;
}