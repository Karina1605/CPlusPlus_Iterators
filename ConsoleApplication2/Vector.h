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
	static double GetCoef(vector<double>::iterator a, vector<double>::iterator b, const Vector &first)
	{
		vector<double>::iterator i = a;
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
	double Sum();
	double ArithmeticMean();
	static Vector Modify(int a, int b, Vector SourceVector)
	{
		vector<double>::iterator f = SourceVector.v.begin();
		vector<double>::iterator l = SourceVector.v.end()-1;
		double c = GetCoef(f, l, SourceVector);
		vector<double>::iterator i =SourceVector.v.begin()+a;
		while (i != SourceVector.v.begin()+b+1)
		{
			*i += c;
			++i;
		}
		Vector newVec(SourceVector);
		return newVec;
	}
	static Vector Modify(Vector first)
	{
		vector<double> res;
		vector<double>::iterator a = first.v.begin();
		vector<double>::iterator b = first.v.end()-1;
		double coef = GetCoef(a, b, first);
		vector<double>::iterator i = first.v.begin();
		while (i != first.v.end())
		{
			*i += coef;
			++i;
		}
		Vector newV(first);
		return newV;
	}
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
	static Vector ModifyByTransform(Vector first)
	{
		transform(first.v.begin(), first.v.end(), first.v.begin(), Transform(first.v));
		return first;
	}
	static Vector ForEach(Vector first)
	{
		for_each(first.v.begin(), first.v.end(), Foreach(first.v));
		return first;
	}
};