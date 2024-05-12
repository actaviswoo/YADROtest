#include "Handler.h"

Handler::Handler(Data& data) : data_(data) {
  tables_.resize(data_.count_tables, "");
  hours_.resize(data_.count_tables, std::make_pair("", "00:00"));
  profit_.resize(data_.count_tables, 0);
}

std::string Handler::EventHandle() {
  output_ += data_.start + "\n";
  for (auto log : data_.logs) {
    if (!Format::CompareTime(data_.end, log.time)) {
      output_ += log.time + " " + std::to_string(log.id) + " " + log.body +
                 " " + (log.table ? std::to_string(log.table) : "") + "\n";
      Event(log);
    }
  }
  EventLeftAll();
  output_ += data_.end + "\n";
  for (std::size_t i = 0; i < hours_.size(); i++) {
    output_ += std::to_string(i + 1) + " " +
               std::to_string(profit_[i]) +
               " " + hours_[i].second + "\n";
  }
  return output_;
}

void Handler::Event(Log& log) {
  if (log.id == Events::kInArrived) {
    EventInArrived(log);
  } else if (log.id == Events::kInSatDown) {
    EventInSatDown(log);
  } else if (log.id == Events::kInWaiting) {
    EventInWaiting(log);
  } else if (log.id == Events::kInLeft) {
    EventInLeft(log);
  }
}

void Handler::EventInArrived(Log& log) {
  if (!Format::CompareTime(data_.start, log.time)) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " NotOpenYet\n";
    return;
  }
  if (std::find(tables_.begin(), tables_.end(), log.body) != tables_.end() ||
      std::find(waiting_room_.begin(), waiting_room_.end(), log.body) != waiting_room_.end()) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " YouShallNotPass\n";
    return;
  }
  waiting_room_.insert(waiting_room_.begin(), log.body);
}

void Handler::EventInSatDown(Log& log) {
  if (std::find(tables_.begin(), tables_.end(), log.body) == tables_.end() &&
      std::find(waiting_room_.begin(), waiting_room_.end(), log.body) == waiting_room_.end()) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " ClientUnknown\n";
    return;
  }
  if (tables_[log.table - 1] != "" || tables_[log.table - 1] == log.body) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " PlaceIsBusy\n";
    return;
  }
  tables_[log.table - 1] = log.body;
  hours_[log.table - 1].first = log.time;
  waiting_room_.erase(std::find(waiting_room_.begin(), waiting_room_.end(), log.body));
}

void Handler::EventInWaiting(Log& log) {
  if (std::find(tables_.begin(), tables_.end(), "") != tables_.end()) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " ICanWaitNoLonger!\n";
    return;
  }
  std::size_t i = 0;
  while (i < waiting_room_.size()) {
    if (waiting_room_[i] == log.body) {
      break;
    }
    i++;
  }
  if (!(i > waiting_room_.size() - tables_.size() - 1)) {
    waiting_room_.erase(waiting_room_.begin() + i);
    output_ += log.time + " " + std::to_string(Events::kOutLeft) + " " + log.body + "\n";
    return;
  }
}

void Handler::EventInLeft(Log& log) {
  if (std::find(tables_.begin(), tables_.end(), log.body) == tables_.end() &&
      std::find(waiting_room_.begin(), waiting_room_.end(), log.body) == waiting_room_.end()) {
    output_ += log.time + " " + std::to_string(Events::kOutError) + " ClientUnknown\n";
    return;
  }
  if (std::find(waiting_room_.begin(), waiting_room_.end(), log.body) != waiting_room_.end()) {
    waiting_room_.erase(std::find(waiting_room_.begin(), waiting_room_.end(), log.body));
    output_ += log.time + " " + std::to_string(Events::kOutLeft) + " " + log.body + "\n";
    return;
  }
  std::size_t i = 0;
  while (i < tables_.size()) {
    if (tables_[i] == log.body) {
      tables_[i] = "";
      break;
    }
    i++;
  }
  hours_[i].second = Format::SumTime(hours_[i].second, Format::DiffTime(log.time, hours_[i].first));
  profit_[i] += data_.price_per_hour * Format::RoundTime(Format::DiffTime(log.time, hours_[i].first));
  if (!waiting_room_.empty()) {
    tables_[i] = waiting_room_.back();
    output_ += log.time + " " + std::to_string(Events::kOutSatDown) + " " +
               waiting_room_.back() + " " + std::to_string(i + 1) + "\n";
    waiting_room_.pop_back();
    hours_[i].first = log.time;
  } else {
    hours_[i].first = "";
  }
}

void Handler::EventLeftAll() {
  std::set<std::string> all;
  for (auto w : waiting_room_) {
    if (w == "") continue;
    all.insert(w);
  }
  for (std::size_t i = 0; i < data_.count_tables; i++) {
    if (tables_[i] == "") continue;
    all.insert(tables_[i]);
    hours_[i].second = Format::SumTime(
        hours_[i].second, Format::DiffTime(data_.end, hours_[i].first));
    profit_[i] += data_.price_per_hour * Format::RoundTime(hours_[i].second);
  }
  for (auto s : all) {
    output_ += data_.end + " " + std::to_string(Events::kOutLeft) + " " + s + "\n";
  }
}
