#include "CPipe.h"
#include "utils.h"
#include <string>
#include <fstream>
#include<iostream>

using namespace std;
int Pipe :: MaxID = 0;

Pipe::Pipe() {
    id = ++MaxID;
    Name = "Unknown";
    diametr = 0;
    length = 0;
    status = 1;
    in = -1;
    out = -1;
    used = false;
    weight = INFINITY;
    productivity = 0;
}

string Pipe::GetName() const
{
    return Name;
}
void Pipe::SetName(string new_name)
{
   Name = new_name;
}

double Pipe::GetLength() const
{
    return length;
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

double Pipe::GetWeight() const
{
    return weight*length;
}

int Pipe::GetIN() const
{
    return in;
}

void Pipe::SetIN(int new_in)
{
    in = new_in;
}

int Pipe::Getout() const
{
    return out;
}

bool Pipe::GetUsed() const
{
    return used;
}

void Pipe::SetUsed(bool status)
{
    if ((out != -1) || in != -1)
        used = status;
    else used = !status;
}

void Pipe::SetOUT(int new_out)
{
    out = new_out;
}

int Pipe::GetProductivity() const
{
    return productivity;
}

void Pipe::SetProductivity(int new_productivity)
{
    productivity = new_productivity;
}
void Pipe::PipeEdit()
{
    status =!status;
    if (status==true) {
        productivity = 0;
        weight = INFINITY;
    }
    if (status == false) {
        double Temperature = 300;
        double c = 0.0384;//относительная плотность по воздуху
        if (GetStatus() == false) {
            double producrivity = c * sqrt(pow(GetDiametr(), 5) / (Temperature * GetLength()));
            SetProductivity(producrivity);
        }
    }
}
void FuncForProductivity(Pipe& new_Pipe)
{
    if (new_Pipe.status == 0) {
        double Temperature = 300;
        double c = 0.0384;//относительная плотность по воздуху
        if (new_Pipe.GetStatus() == false) {
            double producrivity = c * sqrt(pow(new_Pipe.GetDiametr(), 5) / (Temperature * new_Pipe.GetLength()));
            new_Pipe.SetProductivity(producrivity);
        }
    }
}

ofstream& operator<<(ofstream& fout, const Pipe& Pipe)
{
    fout << Pipe.id << '\n' << Pipe.Name << '\n' << Pipe.diametr << '\n' << Pipe.length << '\n' << Pipe.status << '\n' << Pipe.in << '\n' << Pipe.out << '\n';
    return fout;
}

istream& operator>>(ifstream& fin, Pipe& Pipe)
{
    fin >> Pipe.id;
    fin.ignore();
    getline(fin, Pipe.Name);
    fin >> Pipe.diametr;
    fin >> Pipe.length;
    fin >> Pipe.status;
    fin >> Pipe.in;
    fin >> Pipe.out;
    return fin;
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
    if (Pipe.status != 0) {
        cout << "Труба находится в ремонте" << endl;
        Pipe.productivity = 0;
    }
    else {
        cout << "Труба готова к использованию" << endl;
        Pipe.weight = 1;
        Pipe.productivity=1;
    }
    cout << "Данные о трубе успешно сохранены" << endl;
    return in;
}
