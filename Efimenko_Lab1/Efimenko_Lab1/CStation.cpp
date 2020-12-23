#include "CStation.h"
#include "utils.h"
#include <fstream>

using namespace std;
int compressorStation :: MaxID = 0;

compressorStation::compressorStation()
{
    id = ++MaxID;
    Name = "Unknown";
    Amount = 0;
    InWork = 0;
    efficiency = 0;
}

string compressorStation::GetName() const
{
    return Name;
}

void compressorStation::SetName(string new_name)
{
    Name = new_name;
}

int compressorStation::GetAmount() const
{
    return Amount;
}

int compressorStation::GetInWork() const
{
    return InWork;
}

void compressorStation::SetInWork(int new_InWork)
{
    InWork = new_InWork;
}

void EditCompressor(compressorStation& Station1)
{
    cout << "кол-во цехов в работе: ";
    Station1.SetInWork(getCorrectNumber(0, Station1.GetAmount()));
    cout << "Успешно.Кол-во цехов в работе: " << Station1.GetInWork() << '\n';
}

bool compressorStation::Getefficiency() const
{
    return efficiency;
}

int compressorStation::GetID() const
{

    return id;
}

ofstream& operator<<(ofstream& fout, const compressorStation new_station) {
    fout << new_station.id << "\n" << new_station.Name << "\n" << new_station.Amount << "\n" << new_station.InWork << "\n" << new_station.efficiency << '\n';
    return fout;
}
ifstream& operator >>(std::ifstream& fin, compressorStation& new_station)
{
    fin >> new_station.id;
    fin.ignore();
    getline(fin, new_station.Name);
    fin >> new_station.Amount;
    fin >> new_station.InWork;
    fin >> new_station.efficiency;
    return fin;
}
ostream& operator << (ostream& out, const compressorStation& Station1) // перенос вывода в конструктор класса
{
        out << "MaxID: " << compressorStation::MaxID << "\t" << "ID: " << Station1.id << endl
            << "Название КС: " << Station1.Name << endl
            << "Количество цехов: " << Station1.Amount << endl
            << "Количество цехов в работе: " << Station1.InWork << endl
            << "Эффективность цеха(0 - 1): " << Station1.efficiency << endl;
    return out;
}
istream& operator >> (istream& in, compressorStation& Station1)
{
    cout << "Введите название КС: ";
    while (true){
        in.clear();
        in.ignore(10000, '\n');
        getline(in, Station1.Name); //ввод с пробелами
        if (cin.fail()) {
            cin.clear();
           cin.ignore(10000, '\n');
            cout << "Недопустимое название, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите количество цехов: ";
    while (true) {
        in >> Station1.Amount;
        if (cin.fail() || !(Station1.Amount - (int)Station1.Amount) == 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое кол-во цехов, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите количество цехов в работе: ";
    while (true) {
        in >> Station1.InWork;
        if (cin.fail() 
            || !(Station1.InWork >= 0) 
            || !(Station1.InWork - (int)Station1.InWork) == 0 
            || Station1.InWork > Station1.Amount) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое кол-во (РАБОТАЮЩИХ) цехов, введите ещё раз: ";
        }
        else break;
    }
    cout << "Введите эффективность цеха(0-1): ";
    while (true) {
        in >> Station1.efficiency;
        if (cin.fail() || !(Station1.efficiency >= 0) || (Station1.efficiency > 1)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимый показатель, введите ещё раз: ";
        }
        else break;
    }
    cout << "Данные о КС сохранены" << endl;
    return in;
}

