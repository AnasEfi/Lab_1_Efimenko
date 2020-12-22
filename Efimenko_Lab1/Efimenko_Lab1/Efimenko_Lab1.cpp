// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include "CPipe.h"
#include "utils.h"
#include "CStation.h"
#include "NetWork.h"

using namespace std;

void PrintMenu()
{
    cout << "1.Создать трубу" << endl
        << "2.Изменить статус трубы (в ремонте)" << endl
        << "3.Создать КС" << endl
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
        << "13.Удалить трубу" << endl
        << "14.Удалить КС" << endl
        << "Построить сеть" << endl
        << "15.Провести трубу " << endl
        << "16.Построить граф " << endl
        << "0.Выход" << endl
        << "Выберите действие:";
}


template <typename Type>
Type& SelectItem(unordered_map <int, Type>& m) {
    cout << "Введите номер: ";
    unsigned int index = getCorrectNumber(1u, m.size());
    if (m.find(index) != m.end())
        return m.find(index)->second;
}

template<typename Type, typename T>
vector <int> FindbyFilter(const unordered_map <int, Type>& group, Filter <Type, T> f, T parameter) {
    vector <int> res;
    for (auto& item : group) {
        if (f(item.second, parameter)) {
            res.push_back(item.first);
        }
    }
    return res;
}

bool  Checkbypercent(const compressorStation& Station1, double parameter) {
    double percent;
    percent = floor((Station1.GetInWork())/(Station1.GetAmount()) * 100);
    return percent == parameter;
}
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter) {
    return current_Pipe.GetStatus() == parameter;
}

template<typename Type, typename T>
bool InRepair(unordered_map <int, Type>& m, T id) {
    if (m[id].GetStatus() == 0)
        return true;
    else {
        cout << "Труба в ремонте"; return false;
    }
}


int main() {
    setlocale(LC_ALL, "rus");
    unordered_map <int, Pipe> mPipe ;
    unordered_map <int, compressorStation> mStation;
    unordered_map<int, int> connection_between_Stations;
    NetWork Current_Network;
    
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
                (SelectItem(mPipe)).PipeEdit();
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
            if (!(mStation.size() == 0)) {
                int ID;
                ID= SelectItem(mStation).GetID();
                    EditCompressor(mStation[ID]);
            }
            else cout << "нет станций";
            break;
        }
        case 5: // посмотреть данные о трубах
        {
            for (auto& item : mPipe)
                cout << item.second << endl;
            break;
        }
        case 6: // посмотреть данные о КС
        {
            for (auto& item : mStation)
                cout << item.second << endl;
            break;
        }

        case 7: // записать в файл
        {
            ofstream fout;
            string newfilename, str = ".txt";
            if ((mPipe.size() == 0) && (mStation.size() == 0)) {
                cout << "нет труб и станций" << endl; break;
            }
            cout << "Имя файла: ";
            cin >> newfilename;
            if (!ErrorCin(newfilename)) {
                fout.open(newfilename + str, ios::out);
                if (fout.is_open()) {
                    if (mPipe.size() != 0) {
                        fout << "#" << '\n' << mPipe.size() << '\n';
                        for (auto& item : mPipe)
                            fout << item.second;
                    }
                    if (mStation.size() != 0) {
                        fout << "*" << '\n' << mStation.size() << '\n';
                        for (auto& item : mStation)
                            fout<< item.second;
                    }
                    fout.close();
                }
                else cout << "Ошибка в открытии файла";
            }
            break;
        }
        case 8: // загрузить из файла
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
                    fin >> count;
                    while (count--) {
                        Pipe new_Pipe;
                        fin >> new_Pipe;
                        mPipe.emplace(new_Pipe.GetID(),new_Pipe);
                    }
                    fin.ignore();
                }
                else if (data == "*") {
                    fin >> count;
                    while (count--) {
                        compressorStation new_Station;
                        fin >> new_Station;
                        mStation.emplace(new_Station.GetID(), new_Station);
                    }
                    fin.ignore();
                }
            }
            fin.close();
            break;
        }
        case 9: //найти трубу по ID
        {
            mPipe.size() != 0 ?  cout << mPipe[SelectItem(mPipe).GetID()] : cout << "трубы не существует";
            break;
        }
        case 10: //найти КС по ID
        {
            (mStation.size() != 0) ? cout << mStation[SelectItem(mStation).GetID()] : cout<< "КС не созаданы";  
            break;
        }
        case 11: //найти трубы в ремонте
        {
            bool decision, status;
            cout <<"В ремонте?(1=да;0=нет): ";
            status = getCorrectNumber(0, 1);
            auto result = FindbyFilter(mPipe, Checkbystatus, status);
            for (auto& i : result) {
                cout << mPipe[i];
            }
            cout << "Изменить состояние труб? 0=нет 1=да: ";
            decision = getCorrectNumber(0, 1);
            if (decision == 1) {
                for (auto& i : result)
                    mPipe[i].PipeEdit();
            }
            break;
        }
        case 12: //найти KC % работ. цехов
        {
            double percent;
            cout << "Процент работающих цехов: ";
            percent = getCorrectNumber(0, 1);
            auto result = FindbyFilter(mStation, Checkbypercent, percent);
            for (auto& i : result)
                cout << mStation[i];
            break;
        }
        case 13: //удалить трубу
        {
            int id;
            if (mPipe.size() != 0) {
               id=SelectItem(mPipe).GetID();
                if (mPipe.find(id) != mPipe.end())
                    mPipe.erase(id);
            }
            else cout << "нет труб" << endl;
            break;
        }
        case 14: //удалить KC
        {
            int id;
            if (mStation.size() != 0)
            {
                id = SelectItem(mStation).GetID();
                if (mStation.find(id) != mStation.end()) {
                    mStation.erase(id);

                    for (auto& it : mPipe)
                    {
                        if (it.second.GetIN() == id) it.second.SetIN(-1);
                        if (it.second.Getout() == id) it.second.SetOUT(-1);
                    }
                }
            }
            else cout << "нет КС" << endl;
            break;
        }
        case 15: //Провести трубу
        {
            Current_Network.ConnectPipes(mPipe,mStation);
                break;
         
        }
        case 16: //Получим граф
        {
            Current_Network.Create_Graph(mPipe, mStation);
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

