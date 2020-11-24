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

     string GetName() const {return Name;}
     void SetName(string Name) { this-> Name = Name;}

     double GetLength() const {return length;}
     void SetLength(double length) { this->length = length; }

     double GetDiametr() const { return diametr; }
     void SetDiametr(double diametr) { this->diametr = diametr;}

     bool GetStatus() const {return status;}
     void SetStatus(bool status) { this->status = status; }

     int GetID() const { return id; }
     void SetID(int id) { this->id = id; }
    
   friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
   friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
   
};

