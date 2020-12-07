#include "CStation.h"
#include "utils.h"
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

double compressorStation::GetAmount() const
{
    return Amount;
}

double compressorStation::GetInWork() const
{
    return InWork;
}

void compressorStation::SetInWork(double new_InWork)
{
    InWork = new_InWork;
}

bool compressorStation::Getefficiency() const
{
    return efficiency;
}

bool compressorStation::GetID() const
{
    return id;
}



ostream& operator << (ostream& out, const compressorStation& Station1) // ������� ������ � ����������� ������
{
        out << "MaxID: " << compressorStation::MaxID << "\t" << "ID: " << Station1.id << endl
            << "�������� ��: " << Station1.Name << endl
            << "���������� �����: " << Station1.Amount << endl
            << "���������� ����� � ������: " << Station1.InWork << endl
            << "������������� ����(0 - 1): " << Station1.efficiency << endl;
    return out;
}

istream& operator >> (istream& in, compressorStation& Station1)
{
    cout << "������� �������� ��: ";
    while (true)
    {
        in.clear();
        in.ignore(10000, '\n');
        getline(in, Station1.Name); //���� � ���������
        if (cin.fail())
        {
            cin.clear();
           cin.ignore(10000, '\n');
            cout << "������������ ��������, ������� ��� ���: ";
        }
        else break;
    }
    cout << "������� ���������� �����: ";
    while (true)
    {
        in >> Station1.Amount;
        if (cin.fail() || !(Station1.Amount - (int)Station1.Amount) == 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ ���-�� �����, ������� ��� ���: ";
        }
        else break;
    }
    cout << "������� ���������� ����� � ������: ";
    while (true)
    {
        in >> Station1.InWork;
        if (cin.fail() || !(Station1.InWork >= 0) || !(Station1.InWork - (int)Station1.InWork) == 0 || Station1.InWork > Station1.Amount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ ���-�� (����������) �����, ������� ��� ���: ";
        }
        else break;
    }
    cout << "������� ������������� ����(0-1): ";
    while (true)
    {
        in >> Station1.efficiency;
        if (cin.fail() || !(Station1.efficiency >= 0) || (Station1.efficiency > 1))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ ����������, ������� ��� ���: ";
        }
        else break;
    }
    cout << "������ � �� ���������" << endl;
    return in;
}