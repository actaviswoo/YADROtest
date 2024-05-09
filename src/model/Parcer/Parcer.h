#ifndef MODEL_PARCER_H
#define MODEL_PARCER_H

#include "../Data/Data.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

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

    bool IsValidTime(const std::string& time);
    bool CompareTime(const std::string& t1, const std::string& t2);
    bool IsValidName(const std::string& name);
};

#endif  // MODEL_PARCER_H