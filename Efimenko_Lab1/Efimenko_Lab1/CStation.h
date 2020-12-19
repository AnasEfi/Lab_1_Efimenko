#pragma once
#include <string>
#include "utils.h"
#include <iostream>

using namespace std;

class compressorStation
{
    int id;
    int Amount;
    int InWork;
    float efficiency;
    string Name;
    static int MaxID;
public:
 
    compressorStation();

    string GetName() const;
    void SetName(string new_name);

    int GetAmount() const;
    int GetInWork() const;
    bool Getefficiency() const;
    int GetID() const;

    void SetInWork(int new_InWork);

 
    friend void SaveCompressor(ofstream& fout, const compressorStation Station1);
    friend compressorStation LoadStation(ifstream& fin);
    friend std::ostream& operator << (std::ostream& out, const compressorStation& Station1);
    friend std::istream& operator >> (std::istream& in, compressorStation& Station1);

};

