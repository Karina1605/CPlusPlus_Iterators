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