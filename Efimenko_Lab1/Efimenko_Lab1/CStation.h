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
   

    string GetName() const;
    void SetName(string new_name);

    double GetAmount() const;

    double GetInWork() const;
    void SetInWork(double new_InWork);

    bool Getefficiency() const;

    bool GetID() const;

   friend void SaveCompressor(ofstream& fout, const compressorStation Station1);
    friend compressorStation LoadStation(ifstream& fin);
    friend std::ostream& operator << (std::ostream& out, const compressorStation& Station1);
    friend std::istream& operator >> (std::istream& in, compressorStation& Station1);

};

