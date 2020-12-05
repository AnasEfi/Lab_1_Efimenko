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
   static int MaxID;    //поле общее для всех объектов класса

public:

    Pipe();
    string GetName() const;
    void SetName(string new_name);

    double GetLength() const;
    void SetLength(double new_length);

    double GetDiametr() const;
    int GetID() const;
    bool GetStatus() const;

    void PipeEdit();


  friend void SavePipe(ofstream& fout, const Pipe& Pipe);
  friend Pipe LoadPipe( ifstream& fin);
  friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
  friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
   
};

