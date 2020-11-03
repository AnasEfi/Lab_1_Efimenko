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

public:
    static int MaxID;
    std::string Name;
    compressorStation();
    friend void EditCompressor(compressorStation& Station1);
    friend compressorStation LoadStation(ifstream& fin);
    friend void SaveCompressor(ofstream& fout, const compressorStation Station1);
    friend std::ostream& operator << (std::ostream& out, const compressorStation& Station1);
    friend std::istream& operator >> (std::istream& in, compressorStation& Station1);
    
  


      


};

