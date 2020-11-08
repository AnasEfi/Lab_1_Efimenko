#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"

class Pipe
{
   double diametr;
   double length;
   
public:
    static int MaxID; //поле общее для всех объектов класса
    Pipe(); //конструктор
    //~Pipe(); //деструктор
   // std::string GetName() const;
   // void SetName(std::string);
    std::string Name;
    bool status;
    int id;
    template <typename Type>
    friend bool ExistionOfObjectPipeStation(const Type& x);
    template<typename T>
    friend bool Checkbystatus(const Pipe& Pipe1, T parameter);
    template<typename T>
    friend bool Checkbystatus(const Pipe& Pipe1, T parameter);
    friend void SavePipe(std::ofstream& fout, const Pipe& Pipe);
    friend void PipeEdit(Pipe& Pipe);
    friend Pipe LoadPipe(std::ifstream& fin);
    friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
    friend std::istream& operator >> (std::istream& in, Pipe& Pipe);
    template<typename Type>
    friend bool CheckbyID(const Type& x, int parameter);
    
};

