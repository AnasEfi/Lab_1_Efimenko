// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Tube
{
    string Name;
    
    float price;
    double diametr;
    double length;
    char *ID;

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
    Tube bigTube;
    setlocale(LC_ALL, "rus");
    
    cout << " Введите Имя трубы" << "\n";
    cin >> bigTube.Name;
    cout << "Введите Длину трубы"  << "\n";
    cin >> bigTube.length;
    cout << "Ведите Диаметр трубы" << "\n";
    cin >> bigTube.diametr;
    bigTube.ID = " ";
   
    return bigTube;
}


int main()
{

    Tube bigTube_1;
    bigTube_1.ID = "1A";
    CreateTube;
    cout << bigTube_1;
    return 0;
    
}

