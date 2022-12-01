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
	string operations = "+-/*()";
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
			if ((operations.find(c) >= 0)&(operations.find(c) <= 5))
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
			if ((operations.find(c) >= 0) & (operations.find(c) <= 5))
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

vector <TArithmeticExpression> Obrat_Polska(string infix)
{
	TQueue<TArithmeticExpression> q = Parser(infix);
	vector <TArithmeticExpression> res;
	int priority1;
	int priority2;
	string op = "+-/*";
	TStack<TArithmeticExpression> st;
	char c;
	for (int i = 1; i < q.Size() + 1; i++)
	{
		TArithmeticExpression a = q.GetEl(i);
		switch (a.GetType())
		{
		case operation:
			c = a.GetString()[0];
			switch (c)
			{
			case '(':
				st.Push(a);
				break;
			case '+':case '-':case'*':case'/':
				if (st.IsEmpty())
				{
					st.Push(a);
					break;
				}
				priority1 = op.find(c) / 2;
				while (!st.IsEmpty())
				{
					priority2 = op.find(st.Top().GetString()) / 2;
					if (priority1 <= priority2)
					{
						res.push_back(st.Pop());
					}
					else
					{
						break;
					}
				}
				st.Push(a);
				break;
			case ')':
				while (true)
				{
					if (!st.IsEmpty())
					{
						if (st.Top().GetString() != "(")
						{
							res.push_back(st.Pop());
						}
						else
						{
							st.Pop();
							break;
						}
					}
					else
					{
						throw exception("Net (");
					}
				}
			}
			break;
		case number:
			res.push_back(a);
			break;
		}
	}
	while (st.IsEmpty() != true)
	{
		res.push_back(st.Pop());
	}
	return res;
}

double Calculate(vector<TArithmeticExpression>& v) 
{
	TStack<double> st;
	for (TArithmeticExpression& a : v) 
	{
		if (a.GetType() == operation) 
		{
			double v1 = st.Pop();
			double v2 = st.Pop();
			if (a.GetString() == "+") 
			{
				st.Push(v2 + v1);
			}
			else if (a.GetString() == "-") 
			{
				st.Push(v2 - v1);
			}
			else if (a.GetString() == "*") 
			{
				st.Push(v2 * v1);
			}
			else 
			{
				st.Push(v2 / v1);
			}
		}
		else 
		{
			int val = stoi(a.GetString());
			st.Push(val);
		}
	}
	return st.Pop();
}