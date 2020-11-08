// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include"CPipe.h"
#include "utils.h"
#include "CStation.h"

using namespace std;

//struct Pipe
//{
//  string Name;
//  double diametr;
//    double length;
//   bool status;
//};
//
//struct compressorStation
//{
//    string Name;
//    string ID;
//    double Amount;
//    double InWork;
//    float efficiency;
//};

//template <typename Type>
//Type getCorrectNumber(Type min, Type max)
//{
// Type x;
// while ((cin>>x).fail() || x<min || x>max)
//    {
//        cin.clear();
//        cin.ignore(10000, '\n');
//        cout << "Выберите команду (" << min << "-" << max << "):";
//    }
//return x;
//}

//bool ExistionOfObjectPipe(const Pipe& Pipe) //проверка на существование объекта (труба)
//{
//    bool p;
//    (!(Pipe.Name == "")) ? (p = 1) : (p = 0);
//    return p;
//}
//bool ExistionOfObjectStation(const compressorStation& Station1) //проверка на cуществование объекта (компрес.станция)
//{
//    bool p1;
//    ((Station1.Name != "")) ? (p1 = 1) : (p1 = 0);
//    return p1;
//}

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
        << "10.Загрузить KC из файла" << endl
        << "Фильтры" << endl
        << "11.Найти трубу по имени" << endl
        << "12.Найти трубы в ремонте" << endl
        << "13.Найти КС по названию" << endl
        << "14.Найти КС по проценту незад.цехов" << endl
        << "15.Удалить трубу" << endl
        << "16.Удалить КС" << endl
        << "17.Изменить несколько труб" << endl
        << "0.Выход" << endl
        << "Выберите действие:";
}
/*Pipe CreatePipe()
{
    Pipe Pipe;
    cout << "Введите имя трубы: ";
    while (true)
    {
        cin >> Pipe.Name;
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
        cin >> Pipe.length;
        if (cin.fail() || !IsOK(Pipe.length))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимая длина трубы, введите еще раз: ";
            cin >> Pipe.length;
        }
        else break;
    } cout << "Введите диаметр трубы (мм): ";

    while (true)
    {
        cin >> Pipe.diametr;
        if (cin.fail() || !IsOK(Pipe.diametr))
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
        cin >> Pipe.status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение, введите еще раз: ";
        }
        else break;
    }
    (Pipe.status != 0) ? (cout << "Труба находится в ремонте" << endl) : (cout << "Труба готова к использованию" << endl);
    cout << "Данные о трубе успешно сохранены" << endl;
    return Pipe;
}*/

Pipe LoadPipe(ifstream& fin)
{
    Pipe Pipe;
    if (ExistionOfObjectPipeStation(Pipe))
    {
            fin >> Pipe.Name;
            fin >> Pipe.length;
            fin >> Pipe.diametr;
            fin >> Pipe.status;
            fin.close();
            cout << "Труба загружена" << endl;
     }
    else cout << "Трубы не существует" << endl;
    return Pipe;
  };

void PipeEdit(Pipe& Pipe)
{
    if (ExistionOfObjectPipeStation(Pipe))
    {
        Pipe.status = !Pipe.status;
        cout << "Вы успешно поменяли статус трубы" << endl;
    }
    else cout << "Нет данных" << endl;
}
   
/*void PrintPipe(const Pipe& Pipe)
{ 
    string SOSTOYANIE; //переменная для преобразования bool в "Да\Нет" 
    if (ExistionOfObjectPipe(Pipe) == true)
    {
        (Pipe.status != 0) ? (SOSTOYANIE = "Да") : (SOSTOYANIE = "Нет"); // преобразованиЕ bool в "Да\Нет"
        cout << "Имя трубы: " << Pipe.Name << endl
            << "Длина трубы: " << Pipe.length << endl
            << "Диаметр трубы: " << Pipe.diametr << endl
            << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;
    }
    else cout << "Нет данных" << endl;
}*/

/*istream& operator >> (istream& in, Pipe& Pipe) // оператор ввода 
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
        if (cin.fail() || !IsOK(Pipe.length))
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
        if (cin.fail() || !IsOK(Pipe.diametr))
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
ostream& operator << (ostream& out, const Pipe& Pipe)
{
    string SOSTOYANIE; //переменная для преобразования bool в "Да\Нет" 
    if (ExistionOfObjectPipeStation(Pipe) == true)
    {
        (Pipe.status != 0) ? (SOSTOYANIE = "Да") : (SOSTOYANIE = "Нет"); // преобразованиЕ bool в "Да\Нет"
        out << "Имя трубы: " << Pipe.Name << endl
            << "Длина трубы: " << Pipe.length << endl
            << "Диаметр трубы: " << Pipe.diametr << endl
            << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;
    }
    else cout << "Нет данных" << endl;
    return out;
}
*/

void SavePipe(ofstream& fout, const Pipe& Pipe)
{
    string SOSTOYANIE;
    if (ExistionOfObjectPipeStation(Pipe))
    {
        fout << Pipe.Name << "\n" << Pipe.diametr << "\n" << Pipe.length << endl;
        if (Pipe.status != 0)
            SOSTOYANIE = "Да";
        else
            SOSTOYANIE = "Нет";
        fout << "Труба находится в ремонте:" << SOSTOYANIE << endl;
        fout << "Данные сохранены" << endl;
    }
    else fout << "нет данных" << endl;
}

/*
compressorStation CreatCompr()
{
    compressorStation Station1;
    cout << "Введите название КС: ";
    while (true)
    {
        cin >> Station1.Name;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое название, введите ещё раз: ";
        }
    else break;
    }


    cout << "Введите ID КС: ";
    while (true)
    {
        cin >> Station1.ID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение ID, введите ещё раз: ";
        }
        else break;
    }
  
    cout << "Введите количество цехов: ";

    while (true)
    {  
        cin >>  Station1.Amount;
        if (cin.fail() || !(Station1.Amount-(int)Station1.Amount)==0 )
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
        cin >> Station1.InWork;
        if (cin.fail() || !(Station1.InWork>=0)|| !(Station1.InWork - (int)Station1.InWork) == 0 || Station1.InWork > Station1.Amount)
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
        cin >> Station1.efficiency;
        if (cin.fail() || !(Station1.efficiency>=0) || (Station1.efficiency > 1))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимый показатель, введите ещё раз: ";
        }
        else break;
    }

    cout << "Данные о КС сохранены"<< endl;
    return Station1;
}*/
void EditCompressor(compressorStation& Station1)
{
   
    double shop;
    if (ExistionOfObjectPipeStation(Station1) == true)
    {
        cout << "Добавить или удалить кол-во цехов в работе(укажите кол-во): ";
        while (true)
        {
            cin >> shop;
            if (!(shop - (int)shop == 0) || cin.fail() || abs(shop) + Station1.InWork > Station1.Amount || abs(shop) > Station1.Amount || (shop)+Station1.InWork < 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Недопустимое значение,введите еще раз: ";
            }
            else break;
        }
        Station1.InWork += shop;
        cout << "Успешно.Кол-во цехов в работе: " << Station1.InWork << '\n';
    }
    else cout << "Нет даннных" << endl;
}

/*void PrintStation(const compressorStation& Station1)
{
    if (ExistionOfObjectPipeStation(Station1))
    {
        cout << "Название КС: " << Station1.Name << endl
            << "ID КС: " << Station1.ID << endl
            << "Количество цехов: " << Station1.Amount << endl
            << "Количество цехов в работе: " << Station1.InWork << endl
            << "Эффективность цеха(0 - 1): " << Station1.efficiency << endl;
    }
    else cout << "Нет данных"<<endl;
}*/

void SaveCompressor(ofstream& fout, const compressorStation Station1)
{
    if (ExistionOfObjectPipeStation(Station1))
    {
            fout << Station1.Name << "\n" << Station1.Amount << "\n" << Station1.InWork << "\n" << Station1.efficiency << endl;
            cout << "Данные сохранены" << endl;
    }
    else cout << "Станция не создана" << endl;
}


compressorStation LoadStation(ifstream& fin)
{
    compressorStation Station1;
    int p;
    int n = 0;
    
    if (ExistionOfObjectPipeStation(Station1))
    {
        do
        {
           string s;
            getline(fin, s);
            ++n; //тернарный оператор
            if (n == 4)
                (Station1.Name = s);
                n == 5 ? (Station1.Amount = stoi(s)) :
                n == 6 ? (Station1.InWork = stoi(s)) :
                n == 7 ? (Station1.efficiency = stof(s)) :
                p=0;
        } while (!fin.eof());
    }
    else cout << "Станции не существует";
        cout << "КС загружена" << endl;
    return Station1;
};

Pipe& SelectPipe(vector<Pipe> &groupPipe)
{
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, groupPipe.size());
    return groupPipe[index-1];
}

compressorStation& SelectStation(vector<compressorStation>& group2Station)
{
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, group2Station.size());
    return group2Station[index - 1];
}



template<typename T>
using Filter = bool(*)(const Pipe& Pipe1, T parameter);//вернет bool а получит элемент вектора в соответствии с параметром

template<typename Type>
bool CheckbyName(const Type& x, string parameter)
{
    return x.Name == parameter;
}
template<typename Type>
bool CheckbyID(const Type& x, int parameter)
{
 return x.id == parameter;
}

bool  Checkbystatus(const Pipe& Pipe1, bool parameter)
{
    return Pipe1.status == parameter;
}
template<typename T>
vector <int> FindbyPipeFilter(const vector<Pipe>& group, Filter<T> f, T parameter)
{
    vector <int> res;
    int i = 0;
    for (auto& pipe : group)
    {
        if (f(pipe, parameter))
            res.push_back(i);
        i++;
    }
    return res;
}

template<typename T>
using Filter2 = bool(*)(const compressorStation& Station1, T parameter); //фильтр для компрессорных станций
bool  Checkbypercent(const compressorStation& Station1, double parameter)
{
    double percent;
    percent = floor((Station1.InWork) / (Station1.Amount) * 100);
    return percent == parameter;
}
template<typename T>
vector <int> FindbyStationFilter(const vector<compressorStation>& group2, Filter2<T> f, T parameter)
{
    vector <int> res;
    int i = 0;
    for (auto& Station : group2)
    {
        if (f(Station, parameter))
            res.push_back(i);
        i++;
    }
    return res;
}

void ChangeStatusInGroup(vector<Pipe>& group, vector<int> ID_vector)
{
    int index;
    int i = 0;
    int max = ID_vector.size();
    for (auto& Pipe : group)
    {
        for (auto const&element  : ID_vector)
        if (Pipe.id == element)
        {
            Pipe.status = !Pipe.status;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    vector <Pipe> group;
   
    vector <compressorStation> group2;
    vector<int>ID_vector;
    while (1)
    {
        PrintMenu();
        switch (getCorrectNumber(0, 17))
        {
        case 1: // создать трубу 
 {
            Pipe Pipe1;
            cin >> Pipe1;
            group.push_back(Pipe1);
            break;
        }
        case 2: // загрузить трубу
        {
            ifstream fin;
            fin.open("Text.txt", ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                group.reserve(count);    //опеределим кол-во памяти под студентов(под заданное кол-во объектов)
                while (count--)
                {
                    group.push_back(LoadPipe(fin));
                }
                fin.close();
            }
            else cout << "Ошибка при открытия файла" << endl; 
            break;
        }
        case 3: // показать трубу 
        {
            for (const auto& Pipe1:group) //auto определяет что тип труба
            cout << Pipe1 << endl ;
            break;
        }
        case 4: // сохранить трубу
        {
            ofstream fout;
            ofstream outf("Text.txt", ios::app);
            if (outf.is_open())
            {
                fout << group.size() << endl;
                for (Pipe Pipe1 : group)
                    SavePipe(fout, Pipe1);
                    fout.close();
            }
            else cout << "Ошибка в открытии файла";
            break;
        }
        case 5: // редактировать состояние трубы
        {
            PipeEdit(SelectPipe(group));
            break;
        }
        case 6: // создать станцию
        {
            compressorStation Station1;
            cin >> Station1;
            group2.push_back(Station1);;
            break;
        }
        case 7: // сохранить станцию
        {
                ofstream fout;
                ofstream outf("Text.txt", ios::app);
                if (outf.is_open())
                {
                    fout << group2.size() << endl;
                    for (compressorStation Station1 : group2)
                        SaveCompressor(fout, Station1);
                    fout.close();
                }
                else cout << "Ошибка в открытии файла";

                break;
            }
        case 8: // вывести станцию на экран
        {
            for (const auto& Station1 : group2) //auto определяет что тип cтанция
                cout << Station1 << endl;
            break;
        }
        case 9: // изменить кол-во работающих цехов
        {
            EditCompressor(SelectStation(group2));
            break;
        }
        case 10: //загрузить станцию из файла
        {
            ifstream fin;
            fin.open("Text.txt", ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                group2.reserve(count);    //опеределим кол-во памяти под студентов(под заданное кол-во объектов)
                while (count--)
                {
                    group2.push_back(LoadStation(fin));
                }
                fin.close();
            }
            else cout << "Ошибка при открытия файла" << endl;
            break;
        }
        case 11: //найти трубу по имени
        {
            string name;
            cout << "Имя трубы: ";
            cin >> name;
            for (int i : FindbyPipeFilter(group, CheckbyName, name))
                cout << group[i];
            break;
        } 
        case 12:
        {
            bool decision;
            bool status1;
            cout << "В ремонте?(1=да;0=нет): ";
            cin >> status1;
            for (int i : FindbyPipeFilter(group,Checkbystatus,status1))
                cout << group[i];
            if (status1==true)
                cout << "хотите ввести эти трубы в эксплуатацию?: " ;
            cin >> decision;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Недопустимое название, введите ещё раз: ";
            }
            else break;
        }
        case 13: //найти KC по имени
        {
            string name;
            cout << "Имя KC: ";
            cin >> name;
            for (int i : FindbyStationFilter(group2, CheckbyName, name))
                cout << group[i];
            break;
        }
        case 14: //найти KC % работ. цехов
        {
            double percent;
            cout << "Процент работающих цехов: ";
            cin >> percent;
            for (int i : FindbyStationFilter(group2, Checkbypercent, percent))
                cout << group2[i];
            break;
        }
        case 15: //удалить трубу
        {
            int id;
            cout << "ID трубы: ";
            cin >> id;
            for (int i : FindbyPipeFilter(group, CheckbyID, id))
                group.erase(group.begin() + (id - 1));
            break;
        }
        case 16: //удалить KC
        {
            int id;
            cout << "ID КС: ";
            cin >> id;
            for (int i : FindbyStationFilter(group2, CheckbyID, id))
                group2.erase(group2.begin() + (id - 1));
            break;
        }
        case 17: //изменить несколько труб
        {
            bool desicion;
            
            int i = 1;
            bool finish = 0;
            int ID = 0;
            cout << "введите ID труб через enter: ";
            cin >> ID;
            ID_vector.push_back(ID);
            do
            {
                cout << "Добавить еще трубу? Да=1/Нет=0" << endl;
                cin >> desicion;
                if (!(ErrorCin(desicion)))
                {
                    if (desicion)
                    {
                        ++i;
                        
                        cout << "Введите ID трубы: ";
                        cin >> ID;
                        ID_vector.push_back(ID);
                       
                    }
                    else finish = true;
                } 

            } while (finish == false);
            ChangeStatusInGroup(group, ID_vector);

            break;
        }
        case 0: //выход
        {
            return 0;
            break;
        }
        default:
        {
            cout << "Error" << endl;
        }
        }
        cout << '\n';
    }
    return 0;

}

