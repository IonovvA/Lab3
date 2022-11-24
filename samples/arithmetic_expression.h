#pragma once

#include<string>
#include <map>
#include <vector>
#include "queue.h"
#include "stack.h"

#include<iostream>
using namespace std;

enum TypeElement {
	operation,
	number,
	nothing
};

class TArithmeticExpression
{
private:
	string s;
	TypeElement type;

public:
	TArithmeticExpression(string _str = " ", TypeElement _type = nothing) : str(_str), type(_type) {};

	string GetString() { return s; }

	TypeElement GetType() { return type; }

	friend ostream& operator << (ostream& out, TArithmeticExpression& p) 
	{
		out << "{" << p.s << ", ";
		if (p.type == operation)
			out << "operation";
		else if (p.type == number) 
			out << "value";
		out << "}";
		return out;
	}

	double Calculate(vector<TArithmeticExpression>& t);
};


