#include "CPipe.h"
#include "utils.h"
#include <string>
#include<iostream>


using namespace std;
int Pipe :: MaxID = 0;

Pipe::Pipe()
{
    id = ++MaxID;
    Name = "Unknown";
    diametr = 0;
    length = 0;
}

string Pipe::GetName() const
{
    return Name;
}
void Pipe::SetName(string new_name)
{
    new_name = Name;
}

double Pipe::GetLength() const
{
    return length;
}

void Pipe::SetLength(double new_length)
{
    new_length = length;
}

double Pipe::GetDiametr() const
{
    return diametr;
}

int Pipe::GetID() const
{
    return id;
}

bool Pipe::GetStatus() const
{
    return status;
}

void Pipe::PipeEdit()
{
    status = !status;
}


ostream& operator << (ostream& out, const Pipe& Pipe) // перенос вывода в конструктор класса
{
    string SOSTOYANIE; //переменная для преобразования bool в "Да\Нет" 
        (Pipe.status != 0) ? (SOSTOYANIE = "Да") : (SOSTOYANIE = "Нет"); // преобразованиЕ bool в "Да\Нет"
        out << "MaxID: " << Pipe::MaxID << "\t"<<"ID: "<<Pipe.id<< endl
            << "Имя трубы: " << Pipe.Name << endl
            << "Длина трубы: " << Pipe.length << endl
            << "Диаметр трубы: " << Pipe.diametr << endl
            << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;
    return out;
}
istream& operator >> (istream& in, Pipe& Pipe) // оператор ввода 
{
    while (true)
    {
        cout << "Введите имя трубы: ";
        in.clear();
        in.ignore(10000, '\n');
        getline(in, Pipe.Name); //ввод с пробелами
      
        if (in.fail()) // проверка на ввод 
        {
            in.clear();  //очистка буфера
            in.ignore(10000, '\n');
            cout << "Недопустимое значение, введите другое: ";
        }
        else break;
    }
    cout << "Введите пожалуйста длину трубы (км): ";
    while (true)
    {
        in >> Pipe.length;
        if (cin.fail() || !(Pipe.length>0))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимая длина трубы, введите еще раз: ";
        }
        else break;
    } cout << "Введите диаметр трубы (мм): ";
    while (true)
    {
        in >> Pipe.diametr;
        if (cin.fail() || !(Pipe.diametr>0))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение диаметра, введите еще раз: ";
        }
        else break;
    }
    cout << "Труба находится в ремонте? Введите 0=нет или 1=да: ";
    while (true)
    {
        in >> Pipe.status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение, введите еще раз: ";
        }
        else break;

    }
    if (Pipe.status != 0)
        cout << "Труба находится в ремонте" << endl;
    else
        cout << "Труба готова к использованию" << endl;
    cout << "Данные о трубе успешно сохранены" << endl;
    return in;
}

