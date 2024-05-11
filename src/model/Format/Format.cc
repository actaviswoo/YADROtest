#include "Format.h"

bool Format::IsValidTime(const std::string& time) {
  if (time.empty()) return false;
  std::regex timePattern(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
  return std::regex_match(time, timePattern);
}

int Format::GetHour(const std::string& time) { return stoi(time.substr(0, 2)); }
int Format::GetMinute(const std::string& time) {
  return stoi(time.substr(3, 2));
}

std::string Format::SumTime(const std::string& time1,
                            const std::string& time2) {
  if (time1.empty() || time2.empty()) {
    return "";
  }
  int hour = GetHour(time1) + GetHour(time2);
  int minute = GetMinute(time1) + GetMinute(time2);
  if (minute >= 60) {
    hour++;
    minute -= 60;
  }
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
  return buffer;
}

std::string Format::DiffTime(const std::string& time1,
                             const std::string& time2) {
  if (time1.empty() || time2.empty()) {
    return "";
  }
  int hour1 = GetHour(time1);
  int minute1 = GetMinute(time1);
  int hour2 = GetHour(time2);
  int minute2 = GetMinute(time2);
  int diffHour = hour1 - hour2;
  int diffMinute = minute1 - minute2;
  if (diffMinute < 0) {
    diffHour--;
    diffMinute += 60;
  }
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", diffHour, diffMinute);
  return buffer;
}

int Format::RoundTime(const std::string& time) {
  int hour = GetHour(time);
  int minute = GetMinute(time);
  if (minute > 0) return hour + 1;
  return hour;
}

bool Format::CompareTime(const std::string& time1, const std::string& time2) {
  if (time1.empty() || time2.empty()) return false;
  int hour1 = GetHour(time1);
  int minute1 = GetMinute(time1);
  int hour2 = GetHour(time2);
  int minute2 = GetMinute(time2);
  if (hour1 < hour2) {
    return true;
  } else if (hour1 > hour2) {
    return false;
  } else {
    return minute1 <= minute2;
  }
}

bool Format::IsValidName(const std::string& name) {
  if (name.empty()) return false;
  for (char ch : name) {
    if (!isalnum(ch) && ch != '_' && ch != '-') return false;
  }
  return true;
}
