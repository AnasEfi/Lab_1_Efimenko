#pragma once
#include <string>
#include <iostream>

class Pipe
{
    std::string Name;
    double diametr;
    double length;
    bool status;
public:
    Pipe(); //конструктор
    ~Pipe(); //деструктор
    std::string GetName() const;
    void SetName(std::string);

};

