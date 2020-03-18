#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;
class Vector
{
public:
	vector<double> v;
	Vector();
	Vector(size_t size);
	Vector(vector<double> s);
	~Vector();
	//Добавление элемента в вектор
	void Add(double elem);
	//Удаление эл-та из вектора
	void Remove(double elem);
	//Проверка на пустоту
	bool IsEmpty();
	//Получение последнего эл-та вектора
	double Get();
	//Печать как в файл, так и на экран
	void Print(ostream& st);
	//Очистка вектора
	void Clear();
	//Загрузка Вектора из файла
	static Vector GetFromFile(fstream &s)
	{
		vector<double> resv;
		double buf;
		while (s>>buf)
		{
			resv.push_back(buf);
		}
		s.close();
		Vector res(resv);
		return res;
	}
	//Получение коэффицента (квадратный корень из произведения максимума 
	//и последнего числа (чтобы не было исключительных ситуаций, призведение берется по модулю))
	static double GetCoef(vector<double>::iterator a, vector<double>::iterator b, const Vector &first)
	{
		auto i = a;
		double max = *a;
		bool ok = true;
		while (ok)
		{
			++i;
			if (i == b + 1)
				ok = false;
			else
				if (*i > max)
					max = *i;
		}
		double c = sqrt(abs(max*(*b)));
		return c;
	}
	//Сумма элементов
	double Sum();
	//Среднее арифметическое
	double ArithmeticMean();
	//Перегруженный modify с указанием границ преобразования в векторе
	static Vector Modify(int a, int b, Vector SourceVector)
	{
		auto f = SourceVector.v.begin();
		auto l = SourceVector.v.end()-1;
		double c = GetCoef(f, l, SourceVector);
		auto i =SourceVector.v.begin()+a;
		while (i != SourceVector.v.begin()+b+1)
		{
			*i += c;
			++i;
		}
		Vector newVec(SourceVector);
		return newVec;
	}
	//Стаднартный modify для преобразования всех эл-тов вектора
	static Vector Modify(Vector first)
	{
		vector<double> res;
		auto a = first.v.begin();
		auto b = first.v.end()-1;
		double coef = GetCoef(a, b, first);
		auto i = first.v.begin();
		while (i != first.v.end())
		{
			*i += coef;
			++i;
		}
		Vector newV(first);
		return newV;
	}
	//Функтор для генерации произвольных чисел
	class RandomF
	{
		int Diap;
	public:
		RandomF(int d):Diap(d){}
		int operator()() {
			int s = rand() % 2;

			return (rand() % (Diap + 1))*pow(-1, s);
		}
	};
	//Заполнение файла рандомными числами с помощью random или genetate (выбор алгоритма по bool переменной IsRandom)
	static ofstream FillFile(string FileName, int Count, int Diapazon, bool IsRandom)
	{
		ofstream result;
		result.open(FileName);
		if (IsRandom)
		{
			for (int i = 0; i < Count; ++i)
			{
				int sign = rand() % 2;
				int k = rand() % (Diapazon + 1);
				if (sign)
					k *= (-1);
				result << k << " ";
			}
		}
		else
		{
			vector<float> v(Count);
			generate(v.begin(), v.end(), RandomF(Diapazon));
			for (float el : v)
				result << el << " ";
		}
		result.close();
		return result;
	}
	//Функтор для преобразования с помощью transform
	class  Transform
	{
	private:
		double coef;
	public:

		Transform(vector<double> VD) { coef = GetCoef(VD.begin(), VD.end()-1, VD); };
		double operator()(double x)
		{
			return x + coef;
		}
		~Transform() {};

	
	};
	//Функтор для преобразования с помощью foreach
	class  Foreach
	{
	private:
		double coef;
	public:

		Foreach(vector<double> VD) { coef = GetCoef(VD.begin(), VD.end() - 1, VD); };
		void operator()(double &x)
		{
			x += coef;
		}
		~Foreach() {};


	};
	//Modify с помощью transform
	static Vector ModifyByTransform(Vector first)
	{
		transform(first.v.begin(), first.v.end(), first.v.begin(), Transform(first.v));
		return first;
	}
	//Modify с помощью foreach
	static Vector ForEach(Vector first)
	{
		for_each(first.v.begin(), first.v.end(), Foreach(first.v));
		return first;
	}
};