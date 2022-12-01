#pragma once

#include <iostream>
using namespace std;

template <typename T>
class TStack
{
private:
    T* pMem;
    size_t size;
    size_t top;

public:
    TStack(int _size = 1)
    {
        if (_size <= 0)
        {
            throw "Stack size <= 0";
        }
        top = -1;
        size = _size;
        pMem = new T[size];
    }

    TStack(const TStack<T>& p)
    {
        if (p.pMem == nullptr)
        {
            pMem = nullptr;
            size = 0;
            top = -1;
        }
        else
        {
            size = p.size;
            top = p.top;
            pMem = new T[size];
            copy(p.pMem, p.pMem + size, pMem);
        }
    }

    size_t Size()
    {
        return top + 1;
    }

    bool IsEmpty()
    {
        return top == -1;
    }

    bool IsFull()
    {
        return top == size - 1;
    }

    void Push(const T& val)
    {
        if (IsFull())
        {
            T* tmp = new T[size * 2];
            copy(pMem, pMem + size, tmp);
            delete[] pMem;
            pMem = tmp;
            size *= 2;
        }
        pMem[++top] = val;
    }

    T Pop()
    {
        if (IsEmpty())
        {
            throw exception();
        }
        T v = pMem[top];
        top--;
        return v;
    }

    T Top()
    {
        if (IsEmpty())
        {
            throw exception("Stack is empty");
        }
        return pMem[top];
    }

    friend ostream& operator<<(ostream& out, TStack<T>& st) 
    {
        if (st.IsEmpty()) 
        {
            out << "Stack is empty" << endl;
            return out;
        }
        for (int i = st.top; i >= 0; i--) 
            out << st.pMem[i];
        out << endl;
        return out;
    }

    ~TStack()
    {
        delete[] pMem;
    }
};


