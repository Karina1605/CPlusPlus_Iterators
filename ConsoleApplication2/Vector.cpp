#include "pch.h"
#include "Vector.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include<string>
#include <iterator>
#include <fstream>
using namespace std;

Vector::Vector() :v()
{
}

Vector::Vector(size_t size) : v(size) {}
Vector::Vector(vector<double> s) : v(s) {}
Vector::~Vector()
{
}
void Vector::Add(double elem) { v.push_back(elem); }
void Vector:: Remove(double elem) 
{
	auto el = find(v.begin(), v.end(), elem);
	if (el != v.end())
		v.erase(el);
}
Vector Vector::GetFromFile(fstream &s)
{
	vector<double> resv;
	double buf;
	while (s >> buf)
	{
		resv.push_back(buf);
	}
	s.close();
	Vector res(resv);
	return res;
}

bool Vector::IsEmpty() { return v.size() == 0; }
double Vector::Get()
{
	if (IsEmpty())
		throw exception("Attempt to pop from empty container");
	double res = v.back();
	v.pop_back();
	return res;
}
void Vector::Print(ostream& st)
{
	for (float el : v)
		st << el << " ";
	st << '\n';
}
void Vector::Clear() { v.clear(); }
double Vector::Sum()
{
	double res = 0;
	for (double el : v)
		res += el;
	return res;
}
double Vector::ArithmeticMean()
{
	if (v.size() == 0)
		return 0;
	int c = 0;
	double s = 0;
	for (double el : v)
	{
		s += el;
		++c;
	}
	return s / c;
}
double Vector:: GetCoef(const Vector &first)
{
	auto i = first.v.begin();
	auto b = first.v.end() - 1;
	double max = *i;
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
Vector Vector:: Modify(int a, int b, Vector SourceVector)
{
	//!!!
	if (a > b || a > SourceVector.v.size() || b > SourceVector.v.size() || a < 0 || b < 0)
		return SourceVector;
	double c = GetCoef( SourceVector);
	auto iterator = SourceVector.v.begin() + a;
	//!!!
	while (iterator < SourceVector.v.end() && iterator != SourceVector.v.begin() + b + 1)
	{
		*iterator += c;
		++iterator;
	}
	Vector newVec(SourceVector);
	return newVec;
}
Vector Vector:: Modify(Vector first)
{
	//!!!
	return Modify(0, first.v.size()-1, first);
}
 ofstream Vector::FillFile(string FileName, int Count, int Diapazon, bool IsRandom)
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
 Vector Vector ::ModifyByTransform(Vector first)
 {
	 transform(first.v.begin(), first.v.end(), first.v.begin(), Transform(first.v));
	 return first;
 }
 Vector Vector ::ForEach(Vector first)
 {
	 for_each(first.v.begin(), first.v.end(), Foreach(first.v));
	 return first;
 }