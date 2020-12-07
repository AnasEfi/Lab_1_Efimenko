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
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

void PrintMenu()
{
    cout << "1.Создать трубу" << endl
        << "2.Изменить статус трубы (в ремонте)"<< endl
        << "3.Создать КС"<< endl
        << "4.Изменить количество работающих цехов" << endl
        << "5.Посмотреть данные о трубах" << endl
        << "6.Посмотреть данные о КС" << endl
        << "7.Записать в файл" << endl
        << "8.Загрузить из файла" << endl
        << "Фильтры" << endl
        << "9.Найти трубу по ID" << endl
        << "10.Найти КС по ID" << endl
        << "11.Найти трубы в ремонте" << endl
        << "12.Найти КС по проценту незад.цехов" << endl
        << "13.Изменить несколько труб" << endl
        << "14.Удалить трубу" << endl
        << "15.Удалить КС" << endl
        << "0.Выход" << endl
        << "Выберите действие:";
}

Pipe LoadPipe(ifstream& fin) {
    Pipe Pipe;
            fin.ignore();
            getline(fin, Pipe.Name);
            fin >> Pipe.diametr;
            fin >> Pipe.length;
            fin >> Pipe.status;
    return Pipe;
  }

compressorStation LoadStation(ifstream& fin) {
    compressorStation Station;
    fin.ignore();
    getline(fin, Station.Name);
    fin >> Station.Amount;
    fin >> Station.InWork;
    fin >> Station.efficiency;
    return Station;
}

compressorStation& SelectStation(unordered_map<int, compressorStation>& m) {
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, m.size());

    if (m.find(index) != m.end())
        return m.find(index)->second;
    /* for (auto item : m) {
         if (item.first == index) return item.second;*/
}

void SavePipe(ofstream& fout, const Pipe& Pipe) {
    fout << Pipe.Name <<'\n'<< Pipe.diametr <<'\n'<< Pipe.length <<'\n'<< Pipe.status <<'\n';
        cout << "Данные сохранены" << endl;
}
void SaveCompressor(ofstream& fout, const compressorStation Station1) {
    fout << Station1.Name << "\n" << Station1.Amount << "\n" << Station1.InWork << "\n" << Station1.efficiency << '\n';
}

void EditCompressor(compressorStation& Station1){
    double shop;
        cout << "Добавить или удалить кол-во цехов в работе(укажите кол-во): ";
        while (true){
            cin >> shop;
            if ((shop - (int)shop != 0) 
                || (cin.fail())
                || (abs(shop) + Station1.GetInWork()>Station1.GetAmount()) 
                || (abs(shop) > Station1.GetAmount()) 
                || ((shop)+Station1.GetInWork() < 0)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Недопустимое значение,введите еще раз: ";
            }
            else break;
        }
        Station1.SetInWork(Station1.GetInWork()+shop);
        cout << "Успешно.Кол-во цехов в работе: " << Station1.GetInWork()<< '\n';
}

template <typename Type>
Type& SelectPipe(unordered_map <int, Type> &m) {
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, m.size());
    if (m.find(index) != m.end())
        return m.find(index)->second;
}


template<typename Type, typename T >
using Filter = bool(*)(const Type& group, T parameter);//вернет bool, получит элемент вектора в соответствии с параметром

template<typename Type, typename T>
vector <int> FindbyFilter(const unordered_map <int,Type>& group, Filter <Type,T> f, T parameter) {
    vector <int> res;
    for (auto& item : group) {
        if (f(item.second, parameter)) {
            res.push_back(item.first);
        }
    }
    return res;
}

void ChangeStatusInGroup(vector<Pipe>& group, vector<int> ID_vector) {
    for (auto& Pipe : group)
        for (const auto& id : ID_vector)
            if (Pipe.GetID() == id)
                group[id].PipeEdit();
}
bool  Checkbypercent(const compressorStation& Station1, double parameter) {
    double percent;
    percent = floor((Station1.GetInWork()) / (Station1.GetAmount()) * 100);
    return percent == parameter;
}
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter) {
    return current_Pipe.GetStatus() == parameter;
}

int main() {
    setlocale(LC_ALL, "rus");
    unordered_map <int, Pipe> mPipe ;
    unordered_map <int, compressorStation> mStation;
    vector<int>ID_vector;
    while (1) {
        PrintMenu();
        switch (getCorrectNumber(0, 16)) {
        case 1: // создать трубу 
        {
            Pipe new_Pipe;
            cin >> new_Pipe;
            mPipe.emplace(new_Pipe.GetID(), new_Pipe);
            break;
        }
        case 2: // изменить статус трубы
        {
            if (mPipe.size() != 0) {
                (SelectPipe(mPipe)).PipeEdit();
                cout << "Вы успешно поменяли статус трубы" << endl;
            }
            else cout << "нет труб";
            break;
        }
        case 3: // создать КС
        {
            compressorStation new_Station;
            cin >> new_Station;
            mStation.emplace(new_Station.GetID(), new_Station);
            break;
        }
        case 4: // изменить кол-во работающих цехов
        {
            if (!(mStation.size() == 0)) EditCompressor(SelectStation(mStation));
            else cout << "нет станций";
            break;
            
        }
        case 5: // посмотреть данные о трубах
        {
            for (auto item : mPipe)
                cout << item.second << endl;
            break;
        }
        case 6: // посмотреть данные о КС
        {
            for (auto item : mStation)
                cout << item.second << endl;
            break;
        }
       
        case 7: // записать в файл
        {
            string newfilename, str = ".txt";
            if ((mPipe.size() == 0) && (mStation.size() == 0)) {
                cout << "нет труб и станций" << endl; break;
            }
            cout << "Имя файла: ";
            cin >> newfilename;
            if (!ErrorCin(newfilename)) {
                ofstream outf(newfilename + str, ios::out);
                if (outf.is_open()) {
                    if (mPipe.size() != 0) {
                        outf << "#" << '\n' << mPipe.size() << '\n';
                        for (const auto item : mPipe)
                            SavePipe(outf, item.second);
                    }
                    if (mStation.size() != 0) {
                        outf << "*" << '\n' << mStation.size() << '\n';
                        for (const auto item : mStation)
                            SaveCompressor(outf, item.second);
                    }
                    outf.close();
                }
                else cout << "Ошибка в открытии файла";
            }
            break;
        }
        case 8: // звгрузить из файла
        {
            string newfilename, data, str = ".txt";
            cout << "Имя файла: ";
            cin >> newfilename;
            ifstream fin(newfilename + str, ios::in);
            if (!fin.is_open()) {
                cout << "Ошибка при открытия файла" << endl;
                break;
            }
            int count = -1;
            while (getline(fin, data)) {
                if (data == "") {
                    cout << "файл пуст" << endl;
                    fin.ignore();
                }
                else if (data == "#") {
                    Pipe new_Pipe;
                    fin >> count;
                    while (count--) {
                        mPipe.emplace(new_Pipe.GetID(), new_Pipe = LoadPipe(fin));
                    }
                    fin.ignore();
                }
                else if (data == "*") {
                    compressorStation new_Station;
                    fin >> count;
                    while (count--) {
                        mStation.emplace(new_Station.GetID(), new_Station = LoadStation(fin));
                    }
                    fin.ignore();
                }
            }
            fin.close();
            break;
        }
       
        case 9: //найти трубу по ID
        {
            int id;
                cout << "ID трубы: ";
                cin >> id;
                if (!(ErrorCin(id))) {
                    if (mPipe.find(id) != mPipe.end())
                        cout << mPipe[id];
                }
          break;
        }
        case 10:      //найти КС по ID
       { 
            int id;
            cout << "ID станции: ";
                cin >> id;
                if (!(ErrorCin(id)))
                    if (!(ErrorCin(id))) {
                        if (mStation.find(id) != mStation.end())
                            cout << mStation[id];
                    }
                break;
        }
        case 11: //найти трубы в ремонте
        {
            
        bool decision, decision2;
            bool status1;
            cout << "В ремонте?(1=да;0=нет): ";
            cin >> status1;
            auto result = FindbyFilter(mPipe, Checkbystatus, status1);
            for (auto& i : result) {
                cout << mPipe[i];
            }
             cout << "Изменить состояние труб? 0=нет 1=да: ";
              cin >> decision2;
              if (decision2)
                for (auto& i : result)
                 mPipe[i].PipeEdit();
            break;
          
        }
        case 12: //найти KC % работ. цехов
       {
            double percent;
            cout << "Процент работающих цехов: ";
            cin >> percent;
            auto result = FindbyFilter(mStation, Checkbypercent, percent);
            for (int i : result)
                cout << mStation[result[i-1]];
            break;
        }
        case 13: //удалить трубу
        {
            int id;
            if (mPipe.size() != 0) {
                cout << "ID трубы: ";
                cin >> id;
                if (mPipe.find(id) != mPipe.end())
                    mPipe.erase(id);
            }
            else cout << "нет труб" << endl;
        
        }
        case 14: //удалить KC
        {
           int id;
           if (mStation.size() != 0) {
               cout << "ID трубы: ";
               cin >> id;
               if (mStation.find(id) != mStation.end())
                   mPipe.erase(id);
           }
            else cout << "нет труб" << endl;
        }
        case 15: //изменить несколько труб
        {
          /*  bool desicion;
            int i = 1;
             cout << "ID КС: ";
            cin >> id;
            for (int i : FindbyStationFilter(group2, CheckbyID, id))
                group2.erase(group2.begin() + (id - 1));
            break;*/
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

