#pragma once
#include<iostream>

template<typename Type, typename T >
using Filter = bool(*)(const Type& group, T parameter);//вернет bool, получит элемент вектора в соответствии с параметром

using namespace std;
template <typename Type>
Type getCorrectNumber(Type min, Type max){
    Type x;
    if (min > max){
        x = 0;
    }
    else{
        while ((cin >> x).fail() || x<min || x>max){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Выберите (" << min << "-" << max << "):";
        }
    }
    return x;
}

template <typename T>
bool ErrorCin(const T&) {
    bool p=false;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Недопустимое название, введите ещё раз " ;
        p = true;
    }
    return p;
}

template<typename Type>
bool CheckbyID(const Type& x, int parameter){
    return x.GetID() == parameter;
}

template<typename Type>
bool CheckbyName(const Type& x, string parameter){
    return x.GetName() == parameter;
}

