#pragma once
#include "utils.h"
#include <fstream>
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
   int productivity;

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
    bool GetUsed() const;
    void SetUsed(bool new_status);
    void SetOUT(int new_out);
    int GetProductivity() const;
    void SetProductivity(int new_productivity);

  void PipeEdit();
  friend void FuncForProductivity(Pipe& new_Pipe);
  friend std::ofstream& operator <<(ofstream& fout, const Pipe& Pipe);
  friend std::istream& operator >> (ifstream& fin, Pipe& Pipe);
  friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
  friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
};


