#pragma once

#include <iostream>
using namespace std;

template <typename T>
class TQueue
{
private:
    size_t size;
    size_t start;
    size_t end;
    T* arr;

public:
    TQueue(size_t _size = 1)
    {
        size = _size;
        arr = new T[size];
        end = 0;
        start = next(end);
    }

    size_t next(size_t i) { return ((i + 1) % size); }

    size_t Size() 
    {
        if (Is_Empty())
            return 0;
        if (end < start) 
            return  size - start + end + 1;
        else 
            return end - start + 1;
    }

    bool Is_Empty() 
    {
        if (next(end) == start)
            return true;
        return false;
    }

    bool Is_Full() {
        if (next(next(end)) == start)
            return true;
        return false;
    }

    void Push(T x) 
    {
        if (Is_Full())
        {
            int new_size = size * 2;
            T* tmp = new T[new_size];
            int index = 1;
            for (int i = start; i != next(end); i = next(i)) {
                tmp[index] = arr[i];
                index++;
            }
            if (size)
                delete[]arr;
            arr = tmp;
            end = size - 1;
            start = 1;
            size = new_size;
        }
        end = next(end);
        arr[end] = x;
    }

    T Top()
    {
        return arr[start];
    }

    T Pop() 
    {
        if (Is_Empty())
        {
            throw "Queue is empty";
        }
        T v = arr[start];
        start = next(start);
        return v;
    }

    friend ostream& operator<<(ostream& out, TQueue<T>& q) {
        if (q.Is_Empty()) 
        {
            out << "Queue is empty!" << endl;
            return out;
        }
        for (int i = q.start; i != q.next(q.end); i = q.next(i)) 
            out << q.arr[i];
        out << endl;
        return out;
    }

    ~TQueue() 
    {
        if (size > 0)
            delete[]arr;
    }
};


