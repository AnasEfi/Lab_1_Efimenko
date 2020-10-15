// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Pipe
{
    string Name;
    double diametr;
    double length;
    bool status;
};

struct compressorStation
{
    string Name;
    string ID;
    double Amount;
    double InWork;
    float efficiency;
};
int getCorrectNumber(int min, int max)
{
 int x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Выберите команду (" << min << "-" << max << "):";
        cin >> x;
    } while (cin.fail() || x<min || x>max);
return x;
}

bool IsOK(double d)
{ 
    return d > 0;
}

/*bool FailForKC(double k)
{
    return k > 0 ;
}*/

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
        << "0.Выход" << endl;
}
Pipe CreatePipe()
{
    Pipe x;
    cout << "Пожалуйста,введите имя трубы: ";
    while (true)
    {
        cin >> x.Name;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Недопустимое значение, введите ID ещё раз: ";
        }
        else break;
    }
    cout << "Введите пожалуйста длину трубы (км): ";

    while (true)
    {
        cin >> x.length;
        if (cin.fail() || !IsOK(x.length))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимая длина трубы, введите еще раз: ";
            cin >> x.length;
        }
        else break;
    } cout << "Введите пожалуйста диаметр трубы (мм): ";

    while (true)
    {
        cin >> x.diametr;
        if (cin.fail() || !IsOK(x.diametr))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение диаметра, введите еще раз: ";
        }
        else break;
    }
    cout << "Труба находится в ремонте? Введите пожалуйста 0=нет или 1=да: ";
    while (true)
    {
        cin >> x.status;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение, введите еще раз: ";
        }
        else break;
    }
    if (x.status != 0)
    cout << "Труба находится в ремонте" << endl;
    else
    cout << "Труба готова к использованию" << endl;
    cout << "Данные о трубе успешно сохранены" << endl;
    return x;
}

Pipe LoadPipe()
  {
      ifstream fin;
      Pipe x;
      fin.open("Text.txt", ios::in);
      if (fin.is_open()) 
      {
          fin >> x.Name;
          fin >> x.length;
          fin >> x.diametr;
          fin >> x.status;
          fin.close();
          cout << "Труба загружена" << endl;
      }
      else cout << "Ошибка открытия файла" << endl;
      return x;
  };

void PipeEdit(bool& status, const Pipe x)
{
    if (!(x.Name == ""))
    {
        status = !status;
        cout << "Вы успешно поменяли статус трубы" << endl;
    }
    else cout << "Нет данных" << endl;
}
   
void PrintPipe(const Pipe& x)
{ 
    string SOSTOYANIE;

    if (!(x.Name == ""))
    {
        if (x.status != 0)
            SOSTOYANIE = "Да";
        else
            SOSTOYANIE = "Нет";
        cout << "Имя трубы: " << x.Name << endl
            << "Длина трубы: " << x.length << endl
            << "Диаметр трубы: " << x.diametr << endl
            << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;
    }
    else cout << "Нет данных" << endl;
}
void SavePipe(const Pipe& x)
{
    string SOSTOYANIE;
    ofstream fout;
    ofstream outf("Text.txt", ios::app );
    if (outf.is_open())
    {
        outf << x.Name << "\n" << x.diametr << "\n" << x.length << endl;
        if (x.status != 0)
            SOSTOYANIE = "Да";
        else
            SOSTOYANIE = "Нет";
        outf << "Труба находится в ремонте:" << SOSTOYANIE << endl;
        cout << "Данные сохранены" << endl;
        fout.close();
    }
    else cout << "Ошибка в открытии файла";
}

compressorStation CreatCompr()
{
    compressorStation y;
    cout << "Введите название КС: ";
    while (true)
    {
        cin >> y.Name;
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
        cin >> y.ID;
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
        cin >>  y.Amount;
        if (cin.fail() || !(y.Amount-(int)y.Amount)==0 )
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
        cin >> y.InWork;
        if (cin.fail() || !IsOK(y.InWork)|| !(y.InWork - (int)y.InWork) == 0 || y.InWork > y.Amount)
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
        cin >> y.efficiency;
        if (cin.fail() || !IsOK(y.efficiency) || (y.efficiency > 1))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимый показатель, введите ещё раз: ";
        }
        else break;
    }

    cout << "Данные о КС сохранены"<< endl;
    return y;
}
void EditCompressor(compressorStation& y)
{
    
    double shop;
    if (y.Name != "")
    {
        cout << "Добавить или удалить кол-во цехов в работе(укажите кол-во): ";
        while (true)
        {
            cin >> shop;
            if (!(shop - (int)shop == 0) || cin.fail() || abs(shop) + y.InWork > y.Amount || abs(shop) > y.Amount || (shop)+y.InWork < 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Недопустимое значение,введите еще раз: ";
            }
            else break;
        }
        y.InWork +=  shop;
        cout << "Успешно.Кол-во цехов в работе: " << y.InWork << '\n';
    }
    else cout << "Нет даннных" << endl;

}

void PrintStation(const compressorStation& y)
{
    if (!(y.Name ==""))
    
        cout << "Название КС: " << y.Name << endl
            << "ID КС: " << y.ID << endl
            << "Количество цехов: " << y.Amount << endl
            << "Количество цехов в работе: " << y.InWork << endl
            << "Эффективность цеха(0 - 1): " << y.efficiency << endl;
    
    else cout << "Нет данных"<<endl;
}
void SaveCompressor(const compressorStation& y)
{
   
    ofstream fout;
    ofstream outf("Text.txt", ios::app);
    if (outf.is_open())
    {
        outf << y.Name << "\n" << y.ID << "\n" << y.Amount << "\n" << y.InWork << "\n" << y.efficiency << endl;
        cout << "Данные сохранены" << endl;
        fout.close();
    }
    else cout << "Ошибка в открытии файла" << endl;
}

compressorStation LoadStation()
{

    compressorStation y;
    ifstream fin;
    int p;
    string s;
    int n = -1;
    fin.open("Text.txt", ios::in);
    if (fin.is_open())
    {
        do
        {
            string s;
            getline(fin, s);
            ++n; //тернарный оператор
            (n == 4) ? y.Name = s : ++p;
            (n == 5) ? y.ID = s : ++p ;
            (n == 6) ? y.Amount = stoi(s) : ++p;
            (n == 7)? y.InWork = stoi(s) : ++p ;
            (n == 8) ? y.efficiency = stof(s) : ++p ;
           
           /* {

                y.Name = s;
            }

            if (n == 5)
            {

                y.ID = s;
            }

            if (n == 6)
            {

                y.Amount = stoi(s);
            }

            if (n == 7)
            {
                y.InWork = stoi(s);
            }

            if (n == 8)
            {
                y.efficiency = stof(s);
            }
            */
        } while (!fin.eof());
        fin.close();
    }
    else cout << "Ошибка в открыии файла";
        
        cout << "КС загружена" << endl;
    return y;
};

int main()
{
    setlocale(LC_ALL, "rus");
    Pipe x;
    compressorStation y;
 
    while (1)
    {
        PrintMenu();
        switch (getCorrectNumber(0, 10))
        {
        case 1:
        {
            x = CreatePipe();
            break;
        }
        case 2:
        {
            x = LoadPipe();

            break;
        }
        case 3:
        {
            PrintPipe(x);
            break;
        }
        case 4:
        {
            SavePipe(x);
            break;
        }
        case 5:
        {
            PipeEdit(x.status, x);
            break;
        }
        case 6:
        {
            y = CreatCompr();
            break;
        }
        case 7:
        {
            SaveCompressor(y);
            break;
        }
        case 8:
        {
            PrintStation(y);
            break;
        }
        case 9:
        {
            EditCompressor(y);
            break;
        }
        case 10:
        {
            y = LoadStation();
            break;
        }
        case 0:
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

