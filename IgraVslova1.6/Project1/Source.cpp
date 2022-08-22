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
const char ALPHABET[30] = { 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'э', 'ю', 'я' };

void RussianLocalization() {
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);// Вывод на консоль в кодировке 1251. Нужно только будет изменить шрифт консоли на Lucida Console или Consolas
	setlocale(LC_ALL, "rus");
}
void DictionaryFullnessOutput() {
	for (int i = 0; i < 30; i++) {
		for (auto now : DICTIONARY[i]) {
			cout << now << " ";
		}
		cout << endl;
		cout << "==================================================================================================" << endl;
		cout << "ГРУППА СЛОВ С КЛЮЧОМ" << i << endl;
		cout << endl;
		cout << endl;
	}
}
void PrintGameRules()
{
	cout << "Добро пожаловать! Рады приветствовать вас в нашей игре." << endl;
	cout << "Суть игры заключается в том, чтобы придумать новое слово ,начинающее на букву, которым заканчивается предыдущее слово соперника." << endl;
	cout << "Если предыдущее слово заканчивается на буквы ы,ъ,ь, то берём букву, стоящую перед ними." << endl;
	cout << "В начале игры вы можете выбрать уровень сложности, в зависимости от него у вас будет ограничения по времени на каждое новое слово: " << endl;
	cout << "1 - новичок (30 секунд на слово)." << endl;
	cout << "2 - продвинутый (20 секунд на слово)." << endl;
	cout << "3 - профи (10 секунд на слово)." << endl;
	cout << "Если вы не смогли уложиться во время, то вы терпите поражение." << endl;
	cout << "У вас также есть возможность выбрать игровой режим: игра с компьютером или человек против человека. " << endl;
	cout << "В нашей игре действует система рейтинга, которая будет мотивировать вас ставить новые и новые рекорды." << endl;
	cout << "Система рейтинга:" << endl;
	cout << "1. Баллы начисляются за каждый правильный ответ." << endl;
	cout << "2. Кол-во начисляемых баллов зависит от выбранной сложности (1 балл за сложность 'новичок' , 2 балла за 'продвинутый', 3 балла за 'профи')." << endl;
	cout << "В конце игры вы сможете увидеть свой результат, а также ваш собственный рекорд в этой игре." << endl;
	cout << "В этой игре также действует проверка на актуальность(то есть если слово уже вводилось вами раннее,то программа потребует ввести другое слово" << endl;
	cout << "В начале игры вы выбираете, на сколько слов компьютера вы сможет дать ответ и вводите это количество. (Если в конечном счёте у вас это получилось,то вы можете либо закончить игру,посмотрев свой результат,либо перейти на следующую, более сложную стадию)" << endl;
	cout << "Если вы не успели ответить на определенное кол-во слов, то вы проигрываете." << endl;
	cout << "Это все правила, которые вам следует знать.Внимательно их прочитайте и начинайте игру." << endl;
	cout << "Удачи!!!" << endl;
}
int Hardness_choose() {
	cout << "Выберите уровень сложности:" << endl;
	cout << "1 - <<новичок>>" << endl;
	cout << "2 - <<что-то знающий>>" << endl;
	cout << "3 - <<профи>>" << endl;
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
	time_t deadline = time(0) + wait; //создается таймер, который идет от изначального значения(зависит от выбранной сложности) к 0

	while (wait > 0)
	{
		if (WaitForSingleObject(handle, wait * 1000) == WAIT_OBJECT_0)
		{
			if (_kbhit())
			{
				char ch = _getch();
				if (ch >= 'А' && ch <= 'я') // проверка, что каждый введеный символ - это буква
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
		wait = deadline - time(0); //каждый проход цикла вычитаем прошедшее на компьютере время
	}

	_putch('\n');
	_putch('\r');

	return answer;
}
int naib; // максимальный рекод, который был достигнут в текущей игровой сессии
int naib1; // максимальный рекорд, импортированный из файла
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
	string s1; // Первый игрок
	string s2; // Второй игрок
	int h = Hardness_choose();
	int brik = 0;
	cout << "Игра началась!" << endl;
	while (true) {

		cout << "Ход 1 игрока: ";
		if (h == 1) s1 = WaitAnswer(30);
		if (h == 2) s1 = WaitAnswer(20);
		if (h == 3) s1 = WaitAnswer(10);
		if (s1.empty())
		{
			cout << "Время истекло! Первый игрок проиграл.";
			break;
		}
		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s1) {
				cout << "Введенное слово не прошло проверку на уникальность! Введите другое: ";
				brik = 1;
			}
		}
		if (brik == 1) {
			if (h == 1) s1 = WaitAnswer(30);
			if (h == 2) s1 = WaitAnswer(20);
			if (h == 3) s1 = WaitAnswer(10);
		}
		unic.push_back(s1);
		if (s1[s1.length() - 1] == 'ъ' or s1[s1.length() - 1] == 'ы' or s1[s1.length() - 1] == 'ь') {
			s1.resize(s1.length() - 1); // удаляем последнюю букву слова, если она подходит по условию
		}

		cout << "Ход 2 игрока: ";
		if (h == 1) s2 = WaitAnswer(30);
		if (h == 2) s2 = WaitAnswer(20);
		if (h == 3) s2 = WaitAnswer(10);
		if (s2.empty())
		{
			cout << "Время истекло! Второй игрок проиграл.";
			break;
		}
		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s2) {
				cout << "Введенное слово не прошло проверку на уникальность! Введите другое: ";
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
			cout << "Игрок 2 проиграл, Игрок 1 выиграл!";
			break;
		}
		if (s2[s2.length() - 1] == 'ъ' or s2[s2.length() - 1] == 'ы' or s2[s2.length() - 1] == 'ь') {
			s2.resize(s2.length() - 1); // удаляем последнюю букву слова, если она подходит по условию
		}
	}
	cout << endl;
	cout << "=====================================================================================================================" << endl;
}
void RandomWordsInputAndOutput() {
	int h = Hardness_choose();
	string proverka;
	string s1; // Строка для ввода слова пользователем
	time_t time_dedline;
	vector <string> unic = {};
	int k = 0, g = 0, random_num_in_array, x = 0, w, brik = 0;
	srand(time(0)); // выбираем рандомную букву для того, чтобы программа начала игру любым словом на эту букву
	random_num_in_array = rand() % 29;
	while (true) {
		if (proverka.empty() == 1) {
			for (int i = 0; i < 30; i++) {
				if (i == random_num_in_array) {
					for (auto now : DICTIONARY[i]) k++;
					random_num_in_array = rand() % k;
					cout << "Введите сколько минут вы хотите продержаться против компьютера: ";
					cin >> w;
					w *= 60;
					cout << random_num_in_array << " - выбранное рандомное число из диапазона " << k << " в группе слов, начинающихся на буву " << ALPHABET[i] << ": " << endl;
					for (string now : DICTIONARY[i]) {
						g++;
						if (g == random_num_in_array) {
							cout << "Игра началась! Введите слово в ответ на <<" << now << ">> : ";
							time_dedline = time(0) + w;
							proverka = now;
							unic.push_back(proverka);
							if (proverka[proverka.length() - 1] == 'ъ' or proverka[proverka.length() - 1] == 'ы' or proverka[proverka.length() - 1] == 'ь') {
								proverka.resize(proverka.length() - 1); // удаляем последнюю букву слова, если она подходит по условию
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
			cout << "Время, данное на ввод слова, истекло! Вы проиграли. Попробуйте еще раз.";
			break;
		}

		for (vector <string> ::iterator i = unic.begin(); i != unic.end(); i++) {
			if (*i == s1) {
				cout << "Введенное слово не прошло проверку на уникальность! Введите другое: ";
				brik = 1;
			}
		}
		if (brik == 1) {
			if (h == 1) s1 = WaitAnswer(30);
			if (h == 2) s1 = WaitAnswer(20);
			if (h == 3) s1 = WaitAnswer(10);
		}
		unic.push_back(s1);

		if (s1[s1.length() - 1] == 'ъ' or s1[s1.length() - 1] == 'ы' or s1[s1.length() - 1] == 'ь') {
			s1.resize(s1.length() - 1); // удаляем последнюю букву слова, если она подходит по условию
		}

		if ((proverka.empty() == 0 and (proverka[proverka.length() - 1] != s1[0])) or s1 == proverka) {
			if (h * x > naib) naib = h * x;
			cout << "Вы проиграли!" << endl;
			cout << "Ваше количество ответов: " << x << endl;
			cout << "Ваш рейтинг: " << h * x << endl;
			if (naib >= naib1) cout << "Лучший рейтинг: " << naib;
			if (naib < naib1) cout << "Лучший рейтинг: " << naib1;
			break;
		}
		x++;
		w = time_dedline - time(0);
		if (w <= 0) {
			if (h * x > naib) naib = h * x;
			cout << "Конец игры! Ваше количество ответов: " << x << endl;
			cout << "Ваш рейтинг: " << h * x << endl;
			if (naib >= naib1) cout << "Лучший рейтинг: " << naib;
			if (naib < naib1) cout << "Лучший рейтинг: " << naib1;
			break;
		}
		cout << "Последняя буква в введенном слове: " << s1[s1.length() - 1] << endl;

		for (int i = 0; i < 30; i++) {
			if (s1[s1.length() - 1] == ALPHABET[i]) {
				for (auto now : DICTIONARY[i]) k++;
				srand(time(0));
				random_num_in_array = rand() % k;
				cout << random_num_in_array << " - выбранное рандомное число из диапазона " << k << " в группе слов, начинающихся на буву " << ALPHABET[i] << ":" << endl;
				for (string now : DICTIONARY[i]) {
					g++;
					if (g == random_num_in_array) {
						proverka = now; // запоминаем слово, которое выведет программа, для дальнейшей проверки на правильность выполнения условия игры
						if (proverka[proverka.length() - 1] == 'ъ' or proverka[proverka.length() - 1] == 'ы' or proverka[proverka.length() - 1] == 'ь') {
							proverka.resize(proverka.length() - 1); // удаляем последнюю букву слова, если она подходит по условию
						}
						cout << now << endl;
						cout << "Для продложения игры введите новое слово: ";
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
	cout << "Начнем игру?" << endl;

	while (true)
	{
		cout << "\t<<п>> - показать правила игры" << endl;
		cout << "\t<<к>> - играть с компьютером" << endl;
		cout << "\t<<ч>> - играть с человеком" << endl;
		cout << "\t<<з>> - завершить" << endl;

		char action;
		cin >> action;

		if (action == 'к')
		{
			RandomWordsInputAndOutput();
		}
		else if (action == 'ч')
		{
			PvP();
		}
		else if (action == 'п')
		{
			PrintGameRules();
		}
		if (action == 'з')
		{
			break;
		}

		cout << "Продолжим?" << endl;
	}
}
bool LoadDictionary()
{
	string s; // Строка, в которую будет происходить считывание слов из файла
	ifstream file;
	// Открываем файл и проверяем открыт ли он
	file.open("RussianDict.txt");
	if (file.is_open())
	{
		cout << "Файл открыт" << endl;

		// Начало заполнения словаря. Каждый ключ i соответствует элементу с таким же индексом в массиве Alphabet
		while (!file.eof()) {
			file >> s;
			for (int i = 0; i < 30; i++) {
				if (s[0] == ALPHABET[i]) {
					DICTIONARY[i].push_back(s);
				}
			}
		}
		file.close();
		// Конец заполнения словаря
		return true;
	}

	cout << "Файл не открыт, возможно путь указан неверно!" << endl;
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