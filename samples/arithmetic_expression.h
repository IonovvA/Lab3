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
	TArithmeticExpression(string _str = " ", TypeElement _type = nothing) : s(_str), type(_type) {};

	string GetString() { return s; }

	TypeElement GetType() { return type; }

    friend ostream& operator << (ostream& out, TArithmeticExpression& p) 
    {
        out << "{" << p.s << ", ";
        if (p.type == operation) 
            out << "operation";
        else if (p.type == number) 
            out << "number";
        out << "}" << endl;;
        return out;
    }
};

TQueue <TArithmeticExpression> Parser(string infix) 
{
	TQueue<TArithmeticExpression> res;
	infix += ' ';
	int i = 0;
	string tmp = "";
	string operations = "+-*/()";
	string separators = " \n\t";
	int state = 0;
	for (i = 0; i < infix.size(); i++)
	{
		char c = infix[i];
		switch (state)
		{
		case 0: 
			if (c >= '0' && c <= '9') 
			{
				tmp = c;
				state = 1;
				break;
			}
			if (operations.find(c) >= 0)
			{
				tmp = c;
				TArithmeticExpression a(tmp, operation);
				res.Push(a);
				state = 0;
				break;
			}
			break;
		case 1: 
			if (c >= '0' && c <= '9') 
			{
				tmp += c;
				state = 1;
				break;
			}
			if (operations.find(c) >= 0)
			{
				TArithmeticExpression a1(tmp, number);
				res.Push(a1);
				tmp = c;
				TArithmeticExpression a2(tmp, operation);
				res.Push(a2);
				state = 0;
				break;
			}
			if (separators.find(c) >= 0)
			{
				TArithmeticExpression a(tmp, number);
				res.Push(a);
				state = 0;
				break;
			}
			break;
		}
	}
	return res;
};
