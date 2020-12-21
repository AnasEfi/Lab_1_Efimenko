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
    return length;
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

int Pipe::GetUsed() const
{
    return used;
}

void Pipe::SetUsed(bool new_status)
{
    used = true;
}

void Pipe::SetOUT(int new_out)
{
    out = new_out;
}

void Pipe::PipeEdit()
{
    status = !status;
}


void SavePipe(ofstream& fout, const Pipe& Pipe) {
    fout << Pipe.id << '\n' << Pipe.Name << '\n' << Pipe.diametr << '\n' << Pipe.length << '\n' << Pipe.status << '\n' << Pipe.in << '\n' << Pipe.out << '\n';
}

Pipe LoadPipe(ifstream& fin)
{
    Pipe Pipe;
    fin >> Pipe.id;
    fin.ignore();
    getline(fin, Pipe.Name);
    fin >> Pipe.diametr;
    fin >> Pipe.length;
    fin >> Pipe.status;
    fin >> Pipe.in;
    fin >> Pipe.out;
    return Pipe;
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
