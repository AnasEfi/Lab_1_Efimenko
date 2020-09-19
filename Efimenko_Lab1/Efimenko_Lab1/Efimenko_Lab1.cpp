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
    bool repair;
    string help;
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
    cout << "Введите длину трубы в мм" << "\n";
    cin >> x.length;
    cout << "Ведите диаметр трубы в мм" << "\n";
    cin >> x.diametr;
    ofstream outf("Text.txt", ios::app);
    outf << x.Name << "\n" << x.diametr << "\n" << x.length;
    cout << "Труба находится в ремонте? Введите пожалуйста 0=нет или 1=да" << endl;
    cin >> x.repair;
    if (x.repair = true)
    {
        //x.repair = true;
        cout << "Труба находится в ремонте" << endl;
    }
    else if (x.repair= false)
    {
       // x.repair = false;
        cout << "Труба готова к использованию" << endl;
    };
    return x;
}


    int main()
{
    /*ifstream file;
    file.open("Lab_1.txt");*/
    setlocale(LC_ALL, "rus");

Tube Tube1;
Tube1.Name ="ту 14-161-173-97";
cout << "Имя трубы  "<<Tube1.Name<<"\n";
    CreateTube();
    return 0; 
    
}

