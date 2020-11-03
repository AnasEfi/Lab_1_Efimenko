#include "CStation.h"
#include "utils.h"
using namespace std;

int compressorStation :: MaxID = 0;

compressorStation::compressorStation()
{
    id = ++MaxID;
}
ostream& operator << (ostream& out, const compressorStation& Station1) // перенос вывода в конструктор класса
{
    if (ExistionOfObjectPipeStation(Station1))
    {
        out << "MaxID: " << compressorStation::MaxID << "\t" << "ID: " << Station1.id << endl
            << "Название КС: " << Station1.Name << endl
            << "Количество цехов: " << Station1.Amount << endl
            << "Количество цехов в работе: " << Station1.InWork << endl
            << "Эффективность цеха(0 - 1): " << Station1.efficiency << endl;
    }
    else out << "Нет данных" << endl;
    return out;
}

istream& operator >> (istream& in, compressorStation& Station1)
{
    cout << "Введите название КС: ";
    while (true)
    {
        in >> Station1.Name;
        if (cin.fail())
        {
            cin.clear();
           cin.ignore(10000, '\n');
            cout << "Недопустимое название, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите количество цехов: ";
    while (true)
    {
        in >> Station1.Amount;
        if (cin.fail() || !(Station1.Amount - (int)Station1.Amount) == 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое кол-во цехов, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите количество цехов в работе: ";
    while (true)
    {
        in >> Station1.InWork;
        if (cin.fail() || !(Station1.InWork >= 0) || !(Station1.InWork - (int)Station1.InWork) == 0 || Station1.InWork > Station1.Amount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое кол-во (РАБОТАЮЩИХ) цехов, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите эффективность цеха(0-1): ";
    while (true)
    {
        in >> Station1.efficiency;
        if (cin.fail() || !(Station1.efficiency >= 0) || (Station1.efficiency > 1))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимый показатель, введите ещё раз: ";
        }
        else break;
    }
    cout << "Данные о КС сохранены" << endl;
    return in;
}