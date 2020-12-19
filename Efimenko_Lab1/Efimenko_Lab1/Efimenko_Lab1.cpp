// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "utils.h"
#include <cstdio>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include "CStation.h"
#include "CPipe.h"

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
compressorStation LoadStation(ifstream& fin) {
    compressorStation new_station;
    fin >> new_station.id;
    fin.ignore();
    getline(fin, new_station.Name);
    fin >> new_station.Amount;
    fin >> new_station.InWork;
    fin >> new_station.efficiency;
    return new_station;
}
void SaveCompressor(ofstream& fout, const compressorStation new_station) {
    fout << new_station.id << "\n" << new_station.Name << "\n" << new_station.Amount << "\n" << new_station.InWork << "\n" << new_station.efficiency << '\n';
}

Pipe LoadPipe(ifstream& fin) {
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
void SavePipe(ofstream& fout, const Pipe& Pipe) {
    fout << Pipe.id << '\n' << Pipe.Name << '\n' << Pipe.diametr << '\n' << Pipe.length << '\n' << Pipe.status << '\n' << Pipe.in << '\n' << Pipe.out << '\n';
}


void EditCompressor(compressorStation& Station1){
        cout << "кол-во цехов в работе: ";
        Station1.SetInWork(getCorrectNumber(0, Station1.GetAmount()));
        cout << "Успешно.Кол-во цехов в работе: " << Station1.GetInWork()<< '\n';
}

void PrintS(const unordered_map <int, int>& m) {
    for (auto& i : m) {
        cout << i.first << i.second << endl;
    }
}

bool checkAvailablePipe(const unordered_map <int, Pipe>& mPipe) {
    bool p = false;
    for (auto& item : mPipe) {
        if (item.second.GetIN() == -1)
            p = true;
    }
    return p;
}

template <typename Type>
Type& SelectItem(unordered_map <int, Type> &m) {
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

bool  Checkbypercent(const compressorStation& Station1, double parameter) {
    double percent;
    percent = floor((Station1.GetInWork())/(Station1.GetAmount()) * 100);
    return percent == parameter;
}
bool  Checkbystatus(const Pipe& current_Pipe, bool parameter) {
    return current_Pipe.GetStatus() == parameter;
}

/*template<typename Type, typename T>
bool Existofbj(unordered_map <int, Type>& m, T index) {
    if (m.find(index) != m.end())
        return true;
    else {
        cout << "нет КС, введите другое ID: ";
        return false;
    }
}*/

template<typename Type, typename T>
bool InRepair(unordered_map <int, Type>& m, T id) {
    if (m[id].GetStatus() == 0)
        return true;
    else {
        cout << "Труба в ремонте"; return false;
    }
}

void Print(const unordered_set<int> s) {
    for (auto x : s) {
        cout << x <<" ";
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    unordered_map <int, Pipe> mPipe ;
    unordered_map <int, compressorStation> mStation;
    set<int> involved_Pipes;
    set<int> involved_Stations;
    unordered_map <int, int> position_station;
    unordered_map <int, int> position_station_invert;
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
            if (!(mStation.size() == 0)) EditCompressor(SelectItem(mStation));
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
                        for (auto& item : mPipe)
                            SavePipe(outf, item.second);
                    }
                    if (mStation.size() != 0) {
                        outf << "*" << '\n' << mStation.size() << '\n';
                        for (auto& item : mStation)
                            SaveCompressor(outf, item.second);
                    }
                    outf.close();
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
                        auto new_Pipe = LoadPipe(fin);
                        mPipe.emplace(new_Pipe.GetID(),new_Pipe);
                    }
                    fin.ignore();
                }
                else if (data == "*") {
                    fin >> count;
                    while (count--) {
                        auto new_Station =LoadStation(fin);
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
                if (mStation.find(id) != mStation.end())
                    mStation.erase(id);
            }
            else cout << "нет КС" << endl;
            break;
        }
        case 15: //Провести трубу
        {
            int InID = -1;
            int OutID = -1;
            int PipeID = -1;
            auto result = FindbyFilter(mPipe, Checkbystatus, false);
            int inwork = result.size();
            if (checkAvailablePipe(mPipe)==false || mStation.size()<=1 || mPipe.size()==0 || inwork==0) {
                cout << "нет доступных труб или станций" << endl;
                break;
            }
            else {
                cout << "соединить КС [ID]: ";
                OutID = SelectItem(mStation).GetID();
                cout << "c КС [ID]: ";
                while (true) {
                    InID = SelectItem(mStation).GetID();
                   if (InID == OutID) 
                       cout <<"Цех начала трубы,введите другой: " ;
                       else break;
                }

                cout << "трубой [ID]: ";
                do
                PipeID = SelectItem(mPipe).GetID();
                while (mPipe[PipeID].GetStatus() == true);
                    mPipe.find(PipeID)->second.SetIN(InID);
                    mPipe.find(PipeID)->second.SetOUT(OutID);
                break;
            }
        }
        case 16: //Получим граф
        {
            for (auto& item : mPipe) {
                if (item.second.GetStatus() == 0 || item.second.GetIN() != -1 || item.second.Getout() != -1) {
                    involved_Pipes.insert(item.first);
                    involved_Stations.insert(item.second.GetIN());
                    involved_Stations.insert(item.second.Getout());
                }
            }
            int k = 0;
            for (auto i : involved_Stations) {
                position_station.emplace(i, k);
                ++k;
            }
            int d = 0;
            for (auto i : involved_Stations) {
                position_station_invert.emplace(d, i);
                ++d;
            }
            PrintS(position_station);
            PrintS(position_station_invert);
            int x = involved_Stations.size();
            vector<vector<double>> matrix;
            int val = 0;
            for (int i = 0; i < x; i++)
            {
                matrix.push_back(vector<double>());
                for (int j = 0; j < x; j++)
                {
                    matrix.back().push_back(val);
                }
            }

            int indexi, indexj;
            for (auto k : involved_Pipes) {
                for (auto item : mPipe) {
                    if (k == item.first) {
                        indexi = position_station[item.second.Getout()];
                        indexj = position_station[item.second.GetIN()];
                        matrix[indexi][indexj] = item.second.GetWeight();
                        break;
                    }
                }
            }

            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    std::cout << matrix[i][j] << "\t";
                }
                cout << "\n";
            }
            unordered_set<int>sort;
            double sum = 0;
            auto matrix2 = matrix;
            //тополог сортировка
            do {
                for (int j = 0; j < x; j++) {
                    for (int i = 0;i < x;i++) {
                        sum = sum + matrix2[i][j];
                    }
                    if (sum == 0) {
                        sort.insert(j);
                        for (int i = 0; i < x; i++) {
                            if (matrix2[j][i] != 0) {
                                sort.insert(i);
                                matrix2[j][i] = 0;
                            }
                        }
                    }
                }
            } while (sort.size() != involved_Stations.size());
            Print(sort);

           
                for (auto& i : sort) {
                    if (position_station_invert.find(i) != position_station_invert.end())
                        cout<< endl << position_station_invert.find(i)->second;
                }
            
            //преобразование поизций в веришины
        
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

