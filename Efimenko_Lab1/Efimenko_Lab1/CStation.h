#pragma once
#include <string>
#include "utils.h"
#include <iostream>

using namespace std;

class compressorStation
{
    int id;
    double Amount;
    double InWork;
    float efficiency;
    static int MaxID;
    string Name;
public:
    compressorStation();
   

    string GetNameS() const { return Name; }
    void SetNameS(string Name) { this->Name = Name;}

    double GetAmount() const { return Amount; }
    void SetAmount(double Amount) { this->Amount = Amount; }

    double GetInWork() const { return InWork; }
    void SetInWork(double InWork) { this->InWork = InWork; }

    bool Getefficiency() const { return efficiency; }
    void Setefficiency(bool status) { this->efficiency = efficiency; }

    bool GetID() const { return id; }
    void SetID(int id) { this->id = id; }

    friend std::ostream& operator << (std::ostream& out, const compressorStation& Station1);
    friend std::istream& operator >> (std::istream& in, compressorStation& Station1);

};

