#ifndef MODEL_PARCER_H
#define MODEL_PARCER_H

#include "../Data/Data.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Parcer {
    public:
    Parcer(const std::string& filename);
    ~Parcer();
    Data GetData();
    private:
    std::ifstream file_;
    void ReadCountTables(Data& data);
    void ReadStartEnd(Data& data);
    void ReadPricePerHour(Data& data);
    void ReadLogs(Data& data);
};

#endif  // MODEL_PARCER_H