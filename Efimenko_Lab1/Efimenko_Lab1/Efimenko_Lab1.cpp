// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

struct Pipe
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

void PrintMenu()
{
    cout << "1.Создать трубу" << endl
        << "2.Загрузить трубу из файла" << endl
        << "3.Просмотреть данные о трубе" << endl
        << "4.Вывести данные о трубе в файл" << endl
        << "5.Изменить статус трубы (в ремонте)" << endl

        << "6.Создать КС" << endl
        << "7.Сохранить данные о КС в файл" << endl
        << "8.Просмотреть данные о КС" << endl
        << "9.Изменить количество работающих цехов" << endl
        << "0.Выход" << endl;
}
Pipe CreatePipe()
{
    Pipe x;

    cout << "Введите пожалуйста имя трубы в мм: ";
    cin >> x.Name;

    cout << "Введите пожалуйста длину трубы в мм: ";
    cin >> x.length;

    cout << "Введите пожалуйста диаметр трубы в мм: ";
    cin >> x.diametr;

    /*cout << "Труба находится в ремонте? Введите пожалуйста 0=нет или 1=да" << endl;
    cin >> x.repair;
    if (x.repair = true);
    {
        cout << "Труба находится в ремонте" << endl;
    }
    else if (x.repair = false);
    {
        cout << "Труба готова к использованию" << endl;
    };*/
    return x;
};
Pipe LoadPipe()
{
    ifstream fin;
    Pipe x;
    fin.open("Lab_1.txt", ios::in);
    if (fin.is_open())
    {
       
        fin >> x.Name;
        fin >> x.diametr;
        fin >> x.length;
        fin >> x.repair;
        fin >> x.ID;
        fin.close();
    }
    return x;
} 
void PipeEdit(bool& status)
{

    cout << "Изменить значение: Труба находится в ремонте?" << "\n" << "Введите пожалуйста 0 = нет или 1 = да" << endl;
    cin >> status;
    if (status == true)
    {

        cout << "Труба находится в ремонте" << endl;
    }
    else if (status == false)
    {

        cout << "Труба готова к использованию" << endl;
    }
}
   
Pipe PrintPipe(Pipe x)
{
    cout << "Имя трубы: " << x.Name << endl
        << "Длина трубы: " << x.length << endl
        << "Диаметр трубы: " << x.diametr << endl
        << "Статус трубы (в ремонте): " << x.repair << endl;
    return x;
}
void SavePipe(const Pipe& x)
{

    ofstream outf("Text.txt", ios::app);
    outf << "Имя трубы: " << x.Name << "\n" << "Диаметр трубы: " << x.diametr << "\n" << "Длина трубы: " << x.length << endl;
    outf << "Труба находится в ремонте:" << x.repair;
}
int main()

{
    setlocale(LC_ALL, "rus");

    while (1)
    {
        PrintMenu();
        int i = 0;
        cin >> i;
        Pipe x;
        switch (i)
        {
        case 1:
        {
            x = CreatePipe();
            break;
        }
        case 2:
        {
            x = LoadPipe();
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            PipeEdit();
            break;
        }
        case 0:
        { return 0;
        break;
        }
        default:
        {
            cout << "Error" << endl;
        }
        }
        return 0;
    }
}

