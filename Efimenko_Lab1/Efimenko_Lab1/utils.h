#pragma once
#include<iostream>
#include "CPipe.h"


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
        cout << "Недопустимое название, введите ещё раз " << endl;;
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

/*template<typename Type,typename Key, typename Value>
Type& Selection( unordered_map <Key, Value>& m) {
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, m.size());
    for (auto item : m) {
        if (item.first == index) return item.second;
    }
}*/
