#include "Format.h"

bool Format::IsValidTime(const std::string& time) {
    if (time.empty()) 
        return false;
    std::regex timePattern(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
    return std::regex_match(time, timePattern);
}

bool Format::CompareTime(const std::string& time1, const std::string& time2) {
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

bool Format::IsValidName(const std::string& name) {
    if (name.empty())
        return false;
    for (char ch : name) {
        if (!isalnum(ch) && ch != '_' && ch != '-')
            return false;
    }
    return true;
}
