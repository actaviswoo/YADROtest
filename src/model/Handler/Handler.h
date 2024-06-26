#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <set>
#include <vector>
#include <iostream>

#include "../Data/Data.h"
#include "../Format/Format.h"

class Handler {
 public:
  Handler() = delete;
  Handler(Data& data);
  ~Handler() {}
  std::string EventHandle();

 private:
  void Event(Log& id);
  Data& data_;
  std::string output_;
  std::vector<std::string> waiting_room_;
  std::vector<std::string> tables_;
  std::vector<std::pair<std::string, std::string>> hours_;
  std::vector<int> profit_;

  void EventInArrived(Log& log);
  void EventInSatDown(Log& log);
  void EventInWaiting(Log& log);
  void EventInLeft(Log& log);
  void EventLeftAll();
  enum Events {
    kInArrived = 1,
    kInSatDown = 2,
    kInWaiting = 3,
    kInLeft = 4,
    kOutLeft = 11,
    kOutSatDown = 12,
    kOutError = 13
  };
};

#endif  // MODEL_HANDLER_H