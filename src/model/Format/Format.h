#ifndef MODEL_FORMAT_H
#define MODEL_FORMAT_H

#include <string>
#include <regex>

class Format {
    public:
    Format() = delete;
    static bool IsValidTime(const std::string& time);
    static bool CompareTime(const std::string& t1, const std::string& t2);
    static bool IsValidName(const std::string& name); 
};

#endif  // MODEL_FORMAT_H