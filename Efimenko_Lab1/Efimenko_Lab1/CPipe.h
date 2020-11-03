#pragma once
#include <string>
#include <iostream>
#include "utils.h"

class Pipe
{
   double diametr;
   double length;
   bool status;
   int id;

public:
    static int MaxID; //поле общее для всех объектов класса
    Pipe(); //конструктор
    //~Pipe(); //деструктор
   // std::string GetName() const;
   // void SetName(std::string);
    std::string Name;
    friend void SavePipe(std::ofstream& fout, const Pipe& Pipe);
    friend void PipeEdit(Pipe& Pipe);
    friend Pipe LoadPipe(std::ifstream& fin);
    friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
    friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
};

