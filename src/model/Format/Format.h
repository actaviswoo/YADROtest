#ifndef MODEL_FORMAT_H
#define MODEL_FORMAT_H

#include <regex>
#include <string>

class Format {
 public:
  Format() = delete;
  static bool IsValidTime(const std::string& time);
  static bool CompareTime(const std::string& t1, const std::string& t2);
  static bool IsValidName(const std::string& name);
  static int GetHour(const std::string& time);
  static int GetMinute(const std::string& time);
  static std::string SumTime(const std::string& time1,
                             const std::string& time2);
  static std::string DiffTime(const std::string& time1,
                              const std::string& time2);
  static int RoundTime(const std::string& time);
};

#endif  // MODEL_FORMAT_H