#pragma once
#include<iostream>
#include "CPipe.h"


using namespace std;
template <typename Type>
Type getCorrectNumber(Type min, Type max)
{
    Type x;
    while ((cin >> x).fail() || x<min || x>max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "�������� ������� (" << min << "-" << max << "):";
    }
    return x;
}

// bool ExistionOfObjectPipe(const Pipe& Pipe) //�������� �� ������������� ������� (�����)
//{
//    bool p;
//    (!(Pipe.Name == "")) ? (p = 1) : (p = 0);
//    return p;
//}

template <typename Type>
bool ExistionOfObjectPipeStation(const Type& x) //�������� �� ������������� ������� (�����)
{
    bool p;
    (!(x.Name == "")) ? (p = 1) : (p = 0);
   return p;
}

