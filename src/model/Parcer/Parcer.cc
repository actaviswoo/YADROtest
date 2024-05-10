#include "Parcer.h"

Parcer::Parcer(const std::string& filename) : file_(filename) {
    if (!file_.is_open()) {
        throw std::runtime_error("Can't open " + filename);
    }
}

Parcer::~Parcer() {
    if (file_.is_open()) {
        file_.close();
    }
}

Data Parcer::GetData() {
    Data data;
    ReadCountTables(data);
    ReadStartEnd(data);
    ReadPricePerHour(data);
    ReadLogs(data);
    return data;
}

void Parcer::ReadCountTables(Data& data) {
    std::string line;
    if (std::getline(file_, line)) {
        std::istringstream iss(line);
        int count_tables;
        if (!(iss >> count_tables) 
            || count_tables <= 0) {
            throw std::runtime_error("Error line: " + iss.str());
        }
        data.count_tables = count_tables;
    } else {
        throw std::runtime_error("Can't read first line");
    }
}

void Parcer::ReadStartEnd(Data& data) {
    std::string line;
    if (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string start;
        std::string end;
        if (!(iss >> start >> end) 
            || !(Format::IsValidTime(start) && Format::IsValidTime(end))
            || !(Format::CompareTime(start, end))) {
            throw std::runtime_error("Error line: " + iss.str());
        }
        data.start = start;
        data.end = end;
    } else {
        throw std::runtime_error("Can't read second line");
    }
}

void Parcer::ReadPricePerHour(Data& data) {
    std::string line;
    if (std::getline(file_, line)) {
        std::istringstream iss(line);
        int price_per_hour;
        if (!(iss >> price_per_hour) 
            || price_per_hour <= 0) {
            throw std::runtime_error("Error line: " + iss.str());
        }
        data.price_per_hour = price_per_hour;
    } else {
        throw std::runtime_error("Can't read first line");
    }
}

void Parcer::ReadLogs(Data& data) {
    std::string line;
    while (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string time;
        unsigned int id;
        std::string body;
        unsigned int table = 0;
        if (!(iss >> time >> id >> body) 
            || (id > 4) 
            || !(Format::IsValidTime(time))
            || (!data.logs.empty() && !Format::CompareTime(data.logs.back().time, time))
            || (id != 2 && (iss >> table))
            || !(Format::IsValidName(body))) {
            throw std::runtime_error("Error line: " + iss.str());
        }
        if (id == 2) {
            if (!(iss >> table) || table > data.count_tables) {
                throw std::runtime_error("Error line: " + iss.str());
            }
        }
        data.logs.push_back({time, id, body, table});
    }
}
