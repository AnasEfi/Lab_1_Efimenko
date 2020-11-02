#pragma once
#include <string>
#include "utils.h"
#include <iostream>

using namespace std;

class compressorStation
{
    string Name;
    string ID;
    double Amount;
    double InWork;
    float efficiency;

public:
    static int MaxID;
    friend void EditCompressor(compressorStation& Station1);
    friend compressorStation LoadStation();
    friend void PrintStation(const compressorStation& Station1)





};

