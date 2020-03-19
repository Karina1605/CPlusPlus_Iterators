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
	void Add(double elem);
	void Remove(double elem);
	bool IsEmpty();
	double Get();
	void Print(ostream& st);
	void Clear();
	static Vector GetFromFile(fstream &s);
	static double GetCoef(vector<double>::iterator a, vector<double>::iterator b, const Vector &first);
	double Sum();
	double ArithmeticMean();
	static Vector Modify(int a, int b, Vector SourceVector);
	static Vector Modify(Vector first);
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
	static ofstream FillFile(string FileName, int Count, int Diapazon, bool IsRandom);
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
	static Vector ModifyByTransform(Vector first);
	static Vector ForEach(Vector first);
};