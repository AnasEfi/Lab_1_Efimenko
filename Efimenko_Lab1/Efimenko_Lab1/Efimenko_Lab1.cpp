// Efimenko_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
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

bool Fail(double d)
{ 
    return d > 0 && d < 12200;
}

bool FailForKC(double k)
{
    return k > 0 ;
}

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
    cout << "Пожалуйста,введите ID трубы: ";

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
    cout << "Введите пожалуйста длину трубы (мм): ";

    while (true)
    {
        cin >> x.length;

        if (cin.fail() || !Fail(x.length))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимая длина трубы, введите еще раз: ";
            cin >> x.length;
        }
        else
            break;
    }



    cout << "Введите пожалуйста диаметр трубы (мм): ";

    while (true)
    {
        cin >> x.diametr;

        if (cin.fail() || !Fail(x.diametr))
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
        else
            break;
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
      fin.open("Lab_1.txt", ios::in);
      if (fin.is_open())
      {
          fin >> x.Name;
          fin >> x.length;
          fin >> x.diametr;
          fin >> x.status;

          fin.close();
      }
      return x;
  };

void PipeEdit(bool& status)
{
    status = !status;
    cout <<'/n'<< "Вы успешно поменяли статус трубы" << endl;

}
   
void PrintPipe(const Pipe x)
{ 
    string SOSTOYANIE;
    if (x.status != 0)
        SOSTOYANIE = "Да";
    else
        SOSTOYANIE = "Нет";

    cout << "Имя трубы: " << x.Name << endl
        << "Длина трубы: " << x.length << endl
        << "Диаметр трубы: " << x.diametr << endl
        << "Статус трубы (в ремонте): " << SOSTOYANIE << endl;

}
void SavePipe(const Pipe& x)
{
    ofstream fout;
    ofstream outf("Text.txt", ios::app);
    outf << "Имя трубы: "<< x.Name << "\n" << "Диаметр трубы: " << x.diametr << "\n" << "Длина трубы: " << x.length << endl;
    outf << "Труба находится в ремонте:" << x.status;
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
        if (cin.fail() || !FailForKC(y.InWork)|| !(y.InWork - (int)y.InWork) == 0 || y.InWork > y.Amount)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое кол-во (РАБОТАЮЩИХ) цехов, введите ещё раз: ";
        }
        else
            break;
    }

  
    cout << "Введите эффективность цеха(0-1): ";
    while (true)
    {
        cin >> y.efficiency;
        if (cin.fail() || !FailForKC(y.efficiency) || (y.efficiency > 1))
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
    
    double Chex;
   
    cout << "Добавить или удалить кол-во цехов в работе(укажите кол-во): ";
    while (true)
    {
        cin >> Chex;
        if (!(Chex - (int)Chex == 0) || cin.fail() || abs(Chex)+y.InWork>y.Amount || abs(Chex)> y.Amount || (Chex) + y.InWork <0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Недопустимое значение,введите еще раз: ";
        }
        else break;
    }
    y.InWork = y.InWork + Chex;
    cout << "Успешно.Кол-во цехов в работе: "<< y.InWork<<'\n';
   

}

void PrintStation(const compressorStation& y)
{
   cout << "Название КС: " << y.Name << endl
        << "ID КС: " << y.ID << endl
        << "Количество цехов: " << y.Amount << endl
        << "Количество цехов в работе: " << y.InWork << endl
    << "Эффективность цеха(0 - 1): " << y.efficiency << endl;
}
void SaveCompressor(const compressorStation& y)
{
    ofstream fout;
    ofstream outf("Text.txt", ios::app);
    outf << "Имя КС: " << y.Name << "\n" << "ID КС: " << y.ID << "\n" << "Кол-во цехов: " << y.Amount << "\n" << "Кол-во работающих цехов: " << y.InWork << "\n" << "Эффективность: " << y.efficiency << endl;

}

compressorStation LoadStation()
{
   
    compressorStation y;
    string s;
    ifstream fin;
  
    int n = -1;
   
    fin.open("Lab_1.txt", ios::in);
    if (fin.is_open())
    {
        do 
        {
            getline(fin, s);
            ++n;
            if (n == 4)
            {
               
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
          
           

            } while (!fin.eof());
        } fin.close();
    
        
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
        int i = 0;
        cin >> i;

        switch (i)
        {
        case 1:
        {
            x = CreatePipe();
            cout << '\n';
            break;
        }
        case 2:
        {
            x = LoadPipe();
            cout << '\n';
            break;
        }
        case 3:
        {
            PrintPipe(x);
            cout << '\n';
            break;
        }
        case 4:
        {
            SavePipe(x);
            cout << '\n';
            break;
        }
        case 5:
        {
            PipeEdit(x.status);
            cout << '\n';
                
            break;
        }
        case 6:
        {

            y= CreatCompr();
            cout << '\n';
            break;
        }
        case 7:
        {

            SaveCompressor(y);
            cout << '\n';
            break;
        }

        case 8:
        {
            PrintStation(y);
            cout << '\n';
            break;
        }
        case 9:
        {
            EditCompressor(y);
            cout << '\n';
            break;
        }
        case 10:
        {
            y= LoadStation();
            cout << '\n';
            break;
        }
        case 0:

        { return 0;
        break;
        }
        default:
        {
            cout << "Error" << endl;
        }
        }
    }
        return 0;
 
}

