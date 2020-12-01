#pragma once
#include <string>
#include <iostream>
using namespace std;

class Pipe
{
   string Name;
   double diametr;
   double length;
   bool status;
   int id;
   static int MaxID;//поле общее для всех объектов класса

public:
    Pipe();

    string GetName() const;
    void SetName(string new_name);

    double GetLength() const;
    void SetLength(double new_length);

     double GetDiametr() const { return diametr; }
     void SetDiametr(double diametr) { this->diametr = diametr;}

     bool GetStatus() const {return status;}
     void SetStatus(bool status) { this->status = status; }

     int GetID() const { return id; }
     void SetID(int id) { this->id = id; }


   friend Pipe LoadPipe(ifstream& fin, int& number);
   friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
   friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
   
};

