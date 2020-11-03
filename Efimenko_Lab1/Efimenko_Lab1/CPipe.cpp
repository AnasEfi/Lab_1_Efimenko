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
ostream& operator << (ostream& out, const Pipe& Pipe) // перенос вывода в конструктор класса
{
    string SOSTOYANIE; //переменная для преобразования bool в "Да\Нет" 
    if (ExistionOfObjectPipeStation(Pipe))
    {
        (Pipe.status != 0) ? (SOSTOYANIE = "Да") : (SOSTOYANIE = "Нет"); // преобразованиЕ bool в "Да\Нет"
        out << "MaxID: " << Pipe::MaxID << "\t"<<"ID: "<<Pipe.id<< endl
            << "Имя трубы: " << Pipe.Name << endl
            << "Длина трубы: " << Pipe.length << endl
            << "Диаметр трубы: " << Pipe.diametr << endl
            << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;
    }
    else cout << "Нет данных" << endl;
    return out;
}
istream& operator >> (istream& in, Pipe& Pipe) // оператор ввода 
{
    cout << "Введите имя трубы: ";
    while (true)
    {
        in >> Pipe.Name;
        if (cin.fail()) // проверка на ввод 
        {
            cin.clear();  //очистка буфера
            cin.ignore(10000, '\n');
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

//std::string Pipe::GetName() const
//{
//    return std::string();
//}
