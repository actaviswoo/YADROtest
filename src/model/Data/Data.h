#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include <string>
#include <vector>

struct Log {
    std::string time;
    unsigned int id;
    std::string body;
    unsigned int table;
};

struct Data {
    unsigned int count_tables;
    std::string start;
    std::string end;
    unsigned int price_per_hour;
    std::vector<Log> logs;
};

#endif  // MODEL_DATA_H