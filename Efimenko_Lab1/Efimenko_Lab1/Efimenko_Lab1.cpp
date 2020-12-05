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
#include <cstdio>
using namespace std;

void PrintMenu()
{
    cout << "1.Создать трубу" << endl
        << "2.Загрузить из файла" << endl
        << "3.Просмотреть данные о трубе" << endl
        << "4.Вывести данные в файл" << endl
        << "5.Изменить статус трубы (в ремонте)" << endl
        << "6.Создать КС" << endl
        
        << "7.Просмотреть данные о КС" << endl
        << "8.Изменить количество работающих цехов" << endl
        << "9.Загрузить KC из файла" << endl
        << "Фильтры" << endl
        << "10.Найти трубу по ID" << endl
        << "11.Найти трубы в ремонте" << endl
        << "12.Найти КС по ID" << endl
        << "13.Найти КС по проценту незад.цехов" << endl
        << "14.Удалить трубу" << endl
        << "15.Удалить КС" << endl
        << "16.Изменить несколько труб" << endl
        << "0.Выход" << endl
        << "Выберите действие:";
}

Pipe LoadPipe(ifstream& fin)
{
    Pipe Pipe;
            getline(fin,Pipe.Name);
            fin >> Pipe.length;
            fin >> Pipe.diametr;
            fin >> Pipe.status;
       // cout << "Труба загружена" << endl;
    return Pipe;
  }

void SavePipe(ofstream& fout, const Pipe& Pipe)
{
        fout <<Pipe.id << "\n" << Pipe.Name << "\n" << Pipe.diametr << "\n" << Pipe.length << "\n" << Pipe.status<< endl;
        cout << "Данные сохранены" << endl;
}

void EditCompressor(compressorStation& Station1)
{
    double shop;
    {
        cout << "Добавить или удалить кол-во цехов в работе(укажите кол-во): ";
        while (true)
        {
            cin >> shop;
            if (!(shop - (int)shop == 0) || (cin.fail()) || (abs(shop) + Station1.GetInWork() > Station1.GetAmount()) || (abs(shop) > Station1.GetAmount()) || ((shop)+Station1.GetInWork() < 0))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Недопустимое значение,введите еще раз: ";
            }
            else break;
        }
        double shops = Station1.GetInWork();
        shops += shop;
        Station1.SetInWork(shops);
        cout << "Успешно.Кол-во цехов в работе: " << Station1.GetInWork()<< '\n';
    }
}

void SaveCompressor(ofstream& fout, const compressorStation Station1)
{
            fout <<Station1.GetID()<< "\n" << Station1.GetName() << "\n" << Station1.GetAmount() << "\n" << Station1.GetInWork() << "\n" << Station1.Getefficiency() << endl;
            //cout << "Данные сохранены" << endl;
}

compressorStation LoadStation(ifstream& fin)
{
    compressorStation Station;
        getline(fin, Station.Name);
            fin >> Station.Amount;
            fin >> Station.InWork;
            fin >> Station.efficiency;
      
    //cout << "КС загружена" << endl;
    return Station;
};

Pipe& SelectPipe(vector<Pipe> &groupPipe)
{
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, groupPipe.size());
    return groupPipe[index - 1];
}

compressorStation& SelectStation(vector<compressorStation>& group2Station)
{
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, group2Station.size());
    return group2Station[index - 1];
}
template<typename T>
using Filter = bool(*)(const Pipe& Pipe1, T parameter);//вернет bool а получит элемент вектора в соответствии с параметром


bool  Checkbystatus(const Pipe& Pipe1, bool parameter)
{
    return Pipe1.GetStatus() == parameter;
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
    percent = floor((Station1.GetInWork()) / (Station1.GetAmount()) * 100);
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
    for (auto& Pipe : group)
        for (const auto& id : ID_vector)
            if (Pipe.GetID() == id)
                group[id].PipeEdit();
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
        switch (getCorrectNumber(0, 16))
        {
        case 1: // создать трубу 
        {
            Pipe Pipe1;
            cin >> Pipe1;
            group.push_back(Pipe1);
            break;
        }
        case 2: // загрузить из файла
        {
            string newfilename, data, str = ".txt";
            cout << "Имя файла: ";
            cin >> newfilename;
            ifstream fin(newfilename + str, ios::in);
                if (!fin.is_open())
                {
                    cout << "Ошибка при открытия файла" << endl;
                    break;
                }
                int count = -1;
                while (!fin.eof())
                {
                    getline(fin, data);
                    if (data == "")
                    {
                        cout << "файл пуст" << endl;
                    }
                    else if (data == "#")
                    {
                        fin >> count;
                        group.reserve(count);       //опеределим кол-во памяти под трубы(под заданное кол-во объектов)
                        while (count--)
                        {
                            group.push_back(LoadPipe(fin));
                        }
                    }
                    else if (data == "*")
                    {
                        fin >> count;
                        group2.reserve(count);       //опеределим кол-во памяти под станции(под заданное кол-во объектов)
                        while (count--)
                        {
                            group2.push_back(LoadStation(fin));
                        }
                    } cout << fin.tellg(); break;

                }fin.close();
            /*else if (data == "*")
            {
                fin >> count;
                group2.reserve(count);  //опеределим кол-во памяти под станции(под заданное кол-во объектов)
                while (count--)
                {
                    group2.push_back(LoadStation(fin));
                }
            }*/
            break;
        }
        case 3: // показать трубу 
        {
            for (const auto& Pipe1 : group) //auto определяет что тип труба
                cout << Pipe1 << endl;
            break;
        }
        case 4: // сохранить в файл
        {
            string newfilename, str = ".txt";
            cout << "Имя файла: ";
            cin >> newfilename;
            if (!ErrorCin(newfilename))
            {
                ofstream outf(newfilename + str, ios::out);
                if (outf.is_open())
                {
                    outf << "#"<<endl << group.size() << endl;
                    for (Pipe Pipe1 : group)
                        SavePipe(outf, Pipe1);
                    outf <<"*" <<endl<< group2.size() <<endl;
                    for (compressorStation Station1 : group2)
                        SaveCompressor(outf, Station1);
                    if ((group.size() == 0)&&(group2.size()))
                    {
                        cout << "нет труб и станций" << endl;
                    }
                    outf.close();
                }
                else cout << "Ошибка в открытии файла";
            }
            break;
        }
        case 5: // редактировать состояние трубы
        {if (!(group.size() == 0)) {(SelectPipe(group)).PipeEdit(); cout << "Вы успешно поменяли статус трубы" << endl; }
        else cout << "нет труб";
        break;
        }
        case 6: // создать станцию
        {
            compressorStation Station1;
            cin >> Station1;
            group2.push_back(Station1);;
            break;
        }
       
        case 7: // вывести станцию на экран
        {
            for (const auto& Station1 : group2) //auto определяет что тип cтанция
                cout << Station1 << endl;
            break;
        }
        case 8: // изменить кол-во работающих цехов
        {
            if (!(group2.size() == 0)) EditCompressor(SelectStation(group2)); else cout << "нет станций";
            break;
        }
       
        case 9: //найти трубу по ID
        {
            bool check = 0;
            int id;
            while (!check)
            {
                cout << "ID трубы: ";
                cin >> id;
                if (!(ErrorCin(id)))
                {
                    for (int i : FindbyPipeFilter(group, CheckbyID, id))
                    {  cout << group[i]; check=1;}
                }
            } break;
        }
        case 10:      //фильтр в ремонте и пакетное редактирование
        {
            bool decision, decision2;
            bool status1;
            cout << "В ремонте?(1=да;0=нет): ";
            cin >> status1;
            auto result = FindbyPipeFilter(group, Checkbystatus, status1);
            for (int i : result)
                cout << group[i];
                cout << "Изменить состояние труб? 0=нет 1=да: ";
                cin >> decision2;
                if (decision2)
                    for (int i : result)
                    (group[i]).PipeEdit();
            break;
        }
        case 11: //найти KC по ID
        {
            bool check = 0;
            int id;
            while (!check){
            cout << "ID KC: ";
            cin >> id;
            if (!(ErrorCin(id)))
            {
                for (int i : FindbyStationFilter(group2, CheckbyID, id))
                {cout << group2[i]; check = 1;}
            }
        } break;
        }
        case 12: //найти KC % работ. цехов
        {
            double percent;
            cout << "Процент работающих цехов: ";
            cin >> percent;
            for (int i : FindbyStationFilter(group2, Checkbypercent, percent))
                cout << group2[i];
            break;
        }
        case 13: //удалить трубу
        {
            int id;
            cout << "ID трубы: ";
            cin >> id;
            for (int i : FindbyPipeFilter(group, CheckbyID, id))
                group.erase(group.begin() + (id - 1));
            break;
        }
        case 14: //удалить KC
        {
            int id;
            cout << "ID КС: ";
            cin >> id;
            for (int i : FindbyStationFilter(group2, CheckbyID, id))
                group2.erase(group2.begin() + (id - 1));
            break;
        }
        case 15: //изменить несколько труб
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

