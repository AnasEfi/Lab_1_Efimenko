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


ostream& operator << (ostream& out, const Pipe& Pipe) // ������� ������ � ����������� ������
{
    string SOSTOYANIE; //���������� ��� �������������� bool � "��\���" 
        (Pipe.status != 0) ? (SOSTOYANIE = "��") : (SOSTOYANIE = "���"); // �������������� bool � "��\���"
        out << "MaxID: " << Pipe::MaxID << "\t"<<"ID: "<<Pipe.id<< endl
            << "��� �����: " << Pipe.Name << endl
            << "����� �����: " << Pipe.length << endl
            << "������� �����: " << Pipe.diametr << endl
            << "������ ����� (� �������): " << SOSTOYANIE << endl;
    return out;
}
istream& operator >> (istream& in, Pipe& Pipe) // �������� ����� 
{
    while (true)
    {
        cout << "������� ��� �����: ";
        in.clear();
        in.ignore(10000, '\n');
        getline(in, Pipe.Name); //���� � ���������
      
        if (in.fail()) // �������� �� ���� 
        {
            in.clear();  //������� ������
            in.ignore(10000, '\n');
            cout << "������������ ��������, ������� ������: ";
        }
        else break;
    }
    cout << "������� ���������� ����� ����� (��): ";
    while (true)
    {
        in >> Pipe.length;
        if (cin.fail() || !(Pipe.length>0))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ ����� �����, ������� ��� ���: ";
        }
        else break;
    } cout << "������� ������� ����� (��): ";
    while (true)
    {
        in >> Pipe.diametr;
        if (cin.fail() || !(Pipe.diametr>0))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ �������� ��������, ������� ��� ���: ";
        }
        else break;
    }
    cout << "����� ��������� � �������? ������� 0=��� ��� 1=��: ";
    while (true)
    {
        in >> Pipe.status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "������������ ��������, ������� ��� ���: ";
        }
        else break;

    }
    if (Pipe.status != 0)
        cout << "����� ��������� � �������" << endl;
    else
        cout << "����� ������ � �������������" << endl;
    cout << "������ � ����� ������� ���������" << endl;
    return in;
}

