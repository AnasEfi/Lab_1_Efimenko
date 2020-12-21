#pragma once
#include "utils.h"
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
   double weight;
   int in;
   int out;
   static int MaxID;  //поле общее для всех объектов класса
   bool used;

public:

    Pipe();

    string GetName() const;
    void SetName(string new_name);

    double GetLength() const;
    double GetDiametr() const;
    int GetID() const;
    bool GetStatus() const;
    double GetWeight() const;
    
    int GetIN() const;
    void SetIN(int new_in);

    int Getout() const;
    int GetUsed() const;
    void SetUsed(bool new_status);
    void SetOUT(int new_out);

    void PipeEdit();

  friend void SavePipe(ofstream& fout, const Pipe& Pipe);
  friend Pipe LoadPipe(ifstream& fin);
  friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
  friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
};
void SavePipe(ofstream& fout, const Pipe& Pipe);
Pipe LoadPipe(ifstream& fin);

