#include "CPipe.h"
#include "utils.h"


using namespace std;

int Pipe :: MaxID = 0;

Pipe::Pipe()
{
    id = ++MaxID;
}
//Pipe::Pipe(std::string Name)
//{
//    Name = new_name;
//    status = false;
//    Name = "";
//}
//std::string Pipe::GetName() const
//{
//    return Name;
//}
//
//void Pipe::SetName(std::string new_name)
//{
//    Name = new_name;
//}
ostream& operator << (ostream& out, const Pipe& Pipe) // ������� ������ � ����������� ������
{
    string SOSTOYANIE; //���������� ��� �������������� bool � "��\���" 
    if (ExistionOfObjectPipeStation(Pipe))
    {
        (Pipe.status != 0) ? (SOSTOYANIE = "��") : (SOSTOYANIE = "���"); // �������������� bool � "��\���"
        out << "MaxID: " << Pipe::MaxID << "\t"<<"ID: "<<Pipe.id<< endl
            << "��� �����: " << Pipe.Name << endl
            << "����� �����: " << Pipe.length << endl
            << "������� �����: " << Pipe.diametr << endl
            << "������ ����� (� �������): " << SOSTOYANIE << endl;
    }
    else cout << "��� ������" << endl;
    return out;
}
istream& operator >> (istream& in, Pipe& Pipe) // �������� ����� 
{
    cout << "������� ��� �����: ";
    while (true)
    {
        in >> Pipe.Name;
        if (cin.fail()) // �������� �� ���� 
        {
            cin.clear();  //������� ������
            cin.ignore(10000, '\n');
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

//std::string Pipe::GetName() const
//{
//    return std::string();
//}
