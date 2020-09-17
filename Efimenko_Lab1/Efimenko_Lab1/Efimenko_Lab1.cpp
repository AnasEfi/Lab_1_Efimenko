// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Tube
{
    string Name;
    double diametr;
    double length;
    string ID;
};

/*struct compressor
{
    std::string str;
    string Name;
    double score;
    float price;
};*/


 Tube CreateTube()
   {
    Tube x;
    cout << "Введите идентификатор трубы" << "\n";
    cin >> x.ID;
    /*cout << "Введите Имя трубы" << "\n";
    cin >> x.Name;*/
    cout << "Введите Длину трубы"  << "\n";
    cin >> x.length;
    cout << "Ведите Диаметр трубы" << "\n";
    cin >> x.diametr;
    return x;
}


int main()
{
setlocale(LC_ALL, "rus");
Tube Tube1;
Tube1.Name = 'ту';
cout << "Введите Имя трубы"\t<<;
    CreateTube();
    return 0;
    
}

