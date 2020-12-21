#pragma once
#include <string>
#include "utils.h"
#include <iostream>

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
    friend compressorStation LoadStation(std::ifstream& fin);
    friend std::ostream& operator << (std::ostream& out, const compressorStation& Station1);
    friend std::istream& operator >> (std::istream& in, compressorStation& Station1);
};
compressorStation LoadStation(std::ifstream& fin);
void SaveCompressor(ofstream& fout, const compressorStation new_station);
void EditCompressor(compressorStation& Station1);