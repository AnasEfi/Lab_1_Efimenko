#pragma once
#include <string>
#include <iostream>
#include "utils.h"
class Pipe
{
  // std::string Name;
   double diametr;
   double length;
   bool status;
   

   friend void PipeEdit(Pipe& Pipe);
   friend Pipe LoadPipe(ifstream& fin);
   friend void SavePipe(ofstream& fout, const Pipe& Pipe);


public:
    //Pipe(); //конструктор
    //~Pipe(); //деструктор
   // std::string GetName() const;
   // void SetName(std::string);
    std::string Name;
    
    friend std::ostream& operator << (std::ostream& out, const Pipe& Pipe);
    friend std::istream& operator >> (std::istream& in, Pipe& Pipe);

    
};

