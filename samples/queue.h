#pragma once

#include <iostream>
using namespace std;

template <typename T>
class TQueue
{
protected:
    size_t size;
    size_t start;
    size_t end;
    T* arr;
 
    size_t next(size_t i) { return ((i + 1) % size); }

public:
    TQueue(size_t _size = 1)
    {
        size = _size;
        arr = new T[size];
        end = 0;
        start = next(end);
    }

    TQueue(const TQueue<T>& q) 
    {
        size = q.size;
        end = q.end;
        start = q.start;
        arr = new T[size];
        for (int i = start; i < next(end); i++)
            arr[i] = q.arr[i];
    }

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
            T* arr2 = new T[size * 2];
            size_t index = 1;
            for (size_t i = start; i < next(end); i = next(i))
            {
                arr2[index] = arr[i];
                index++;
            }
            delete[] arr;
            arr = arr2;
            end = size - 1;
            size *= size;
            start = 1;
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

    ~TQueue() 
    {
        if (size > 0)
            delete[]arr;
    }
};


