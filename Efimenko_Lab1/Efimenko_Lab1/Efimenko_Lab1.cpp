// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
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
    cout << "Введите длину трубы в мм"  << "\n";
    cin >> x.length;
    cout << "Ведите диаметр трубы в мм" << "\n";
    cin >> x.diametr;
    ofstream outf("Text.txt", ios::app);
    outf << x.Name << "\n" << x.diametr << "\n" << x.length;
    return x;
}


int main()
{
    ifstream file;
    file.open("Lab_1.txt");
    setlocale(LC_ALL, "rus");

Tube Tube1;
Tube1.Name ="ту 14-161-173-97";
cout << "Имя трубы  "<<Tube1.Name<<"\n";
    CreateTube();

   
    return 0; 
    
}

