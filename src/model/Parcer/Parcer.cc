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
            || !(IsValidTime(start) && IsValidTime(end))
            || !(CompareTime(start, end))) {
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
            || !(IsValidTime(time))
            || (!data.logs.empty() && !CompareTime(data.logs.back().time, time))
            || (id != 2 && (iss >> table))
            || !(IsValidName(body))) {
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

bool Parcer::IsValidTime(const std::string& time) {
    if (time.empty()) 
        return false;
    std::regex timePattern(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
    return std::regex_match(time, timePattern);
}

bool Parcer::CompareTime(const std::string& time1, const std::string& time2) {
    if (time1.empty() || time2.empty())
        return false;
    int hour1 = stoi(time1.substr(0, 2));
    int minute1 = stoi(time1.substr(3, 2));
    int hour2 = stoi(time2.substr(0, 2));
    int minute2 = stoi(time2.substr(3, 2));
    if (hour1 < hour2) {
        return true;
    } else if (hour1 > hour2) {
        return false;
    } else {
        return minute1 <= minute2;
    }
}

bool Parcer::IsValidName(const std::string& name) {
    if (name.empty())
        return false;
    for (char ch : name) {
        if (!isalnum(ch) && ch != '_' && ch != '-')
            return false;
    }
    return true;
}

