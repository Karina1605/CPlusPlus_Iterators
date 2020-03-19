// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Задание 1А (реализация вектором, Прибавить к каждому числу корень квадратный из произведения максимума и
//последнего числа.)

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<cmath>
#include <ctime>
#include <algorithm>
#include<iterator>
#include "Vector.h"
using namespace std;

int menu()
{
	int res;
	cout << "Задание: ко всем эл-там контейнера прибавить квадратный корень из произведения максимума и последнего числа\n\n";
	cout << "1.Заполнить файл случайными числами(random)\n";
	cout << "2.Заполнить файл случайными числами(generate)\n";
	cout << "3.Заполнить контейнер из файла\n";
	cout << "4.Добавить в контейнер\n";
	cout << "5.Удалить из контейнера\n";
	cout << "6.Изменить контейнер с помощью modify\n";
	cout << "7.Изменить часть контейнера с помощью modify\n";
	cout << "8.Изменить контейнер с помощью tramsform\n";
	cout << "9.Изменить контейнер с помощью for_each\n";
	cout << "10.Вычислить сумму\n";
	cout << "11.Вычислить среднее арифметическое значение\n";
	cout << "12.Вывести результат в файл\n";
	cout << "13.Вывести результат на экран\n";
	cout << "0.Выход\n";
	cin >> res;
	getchar();
	if (cin.fail())
	{
		res = -1;
		cin.clear();
	}
		
	cout << "\n\n";
	return res;
}

int main()
{
	setlocale(LC_ALL, "russian");
	Vector mv;
	Vector res;
	string FileName;
	fstream file;
	int f, l, count, diapazon;
	double buf;
	srand(static_cast<unsigned int>(time(0)));

	int c;
	do
	{
		c = menu();
		switch (c)
		{
		case 0:
			cout << "До свидания\n";
			break;
		case 1:
			cout << "Имя файла : ";
			getline(cin, FileName);

			cout << "Кол-во : ";
			cin >> count;
			cout << "\nДиапазон : ";
			cin >> diapazon;
			Vector::FillFile(FileName, count, diapazon, true);
			break;
		case 2:
			cout << "Имя файла : ";
			getline(cin, FileName);
			cout << "Кол-во : ";
			cin >> count;
			cout << "\nДиапазон : ";
			cin >> diapazon;
			Vector::FillFile(FileName, count, diapazon, false);
			break;
		case 3:
			cout << "Имя файла : ";
			getline(cin, FileName);
			file.open(FileName, std::ios::in);
			mv = Vector::GetFromFile(file);
			file.close();
			mv.Print(cout);
			break;
		case 4:
			cout << "Добавить эл-т : ";
			cin >> buf;
			mv.Add(buf);
			break;
		case 5:
			cout << "Удалить эл-т : ";
			cin >> buf;
			mv.Remove(buf);		
			break;
		case 6:
			res = Vector::Modify(mv);
			res.Print(std::cout);
			break;
		case 7:
			cout << "First pos : ";
			cin >> f;
			cout << "\nLast pos : ";
			cin >> l;
			cout << '\n';
			res = Vector::Modify(f, l, mv);
			res.Print(std::cout);
			break;
		case 8:
			res = Vector::ModifyByTransform(mv);
			res.Print(cout);
			break;
		case 9:
			res = Vector::ForEach(mv);
			res.Print(cout);
			break;
		case 10:
			cout << "Сумма эл-тов равна " << mv.Sum() << "\n";
			break;
		case 11:
			cout << "Средннее арифметическое " << mv.ArithmeticMean() << "\n";
			break;
		case 12:
			cout << "Имя файла : ";
			getline(cin, FileName);
			file.open(FileName, std::ios::out);
			mv.Print(file);
			res.Print(file);
			file.close();
			break;
		case 13:
			mv.Print(cout);
			res.Print(cout);
			break;
		default:
			cout << "Вы должны ввести число от 0 до 13\n";
			break;
		}
	} while (c != 0);
	getchar();
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
