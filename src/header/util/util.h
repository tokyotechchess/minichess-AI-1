#pragma once

template <typename T>
T max(T a, T b) { return (a > b) ? a : b; };
template <typename T>
T min(T a, T b) { return (a < b) ? a : b; };
template <typename T>
T abs(T a) { return a > 0 ? a : -a; };

/*
check whether array "a" is same as array "b" AS SET.
*/
template <typename T>
bool SameAsSet(T *a, T *b, int length)
{
    T _a[length], _b[length];
    int i, j;
    void (*__swap)(T * a, T * b) = []()
    {
        T temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }

    for (i = 0; i < length; i++)
    {
        _a[i] = a[i];
        _b[i] = b[i];
    }

    for (i = 0; i < lenght; i++)
    {
        for (j = 0; j < length - i; j++)
        {
            if (i + j == length - 1)
                return false;
        }
    }
}