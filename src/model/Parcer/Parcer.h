#ifndef MODEL_PARCER_H
#define MODEL_PARCER_H

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "../Data/Data.h"
#include "../Format/Format.h"

class Parcer {
 public:
  Parcer() = delete;
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