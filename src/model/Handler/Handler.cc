#include "Handler.h"
#include <iostream>
Handler::Handler(Data& data) : data_(data) {
    tables_.resize(data_.count_tables, "");
}

std::string Handler::EventHandle() {
    output_ += (data_.start + '\n');
    std::size_t logs_size = data_.logs.size();
    for (auto log : data_.logs) {
        output_ += (log.time + ' ' + std::to_string(log.id) + ' ' + 
                    log.body + ' ' + (log.table ? std::to_string(log.table) : "") + '\n');
        Event(log);
    }
    EventLeftAll();
    output_ += (data_.end + '\n');
    std::cout << output_;
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
    if (!Format::CompareTime(data_.start, log.time) || Format::CompareTime(data_.end, log.time)) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " NotOpenYet\n";
        return;
    }
    if (std::find(tables_.begin(), tables_.end(), log.body) != tables_.end() ||
        std::find(waiting_room_.begin(), waiting_room_.end(), log.body) != waiting_room_.end()) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " YouShallNotPass\n";
        return;
    }
    waiting_room_.insert(waiting_room_.begin(), log.body);
    //     output_ += "---\n";
    // for (auto w : waiting_room_) {
    //     output_ += w + "\n";
    // }
    // output_ += "---\n";
    // for (auto t : tables_) {
    //     output_ += t + "\n";
    // }
    // output_ += "---\n";
}

void Handler::EventInSatDown(Log& log) {
    if (std::find(tables_.begin(), tables_.end(), log.body) == tables_.end() &&
        std::find(waiting_room_.begin(), waiting_room_.end(), log.body) == waiting_room_.end()) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " ClientUnknown\n";
        return;
    }
    if (tables_[log.table - 1] != "" || tables_[log.table - 1] == log.body) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " PlaceIsBusy\n";
        return;
    }
    tables_[log.table - 1] = log.body;
    waiting_room_.erase(std::find(waiting_room_.begin(), waiting_room_.end(), log.body));

    // output_ += "---\n";
    // for (auto w : waiting_room_) {
    //     output_ += w + "\n";
    // }
    // output_ += "---\n";
    // for (auto t : tables_) {
    //     output_ += t + "\n";
    // }
    // output_ += "---\n";
}

void Handler::EventInWaiting(Log& log) {
    if (std::find(tables_.begin(), tables_.end(), "") != tables_.end()) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " ICanWaitNoLonger!\n";
        return;
    }
    if (waiting_room_.size() > tables_.size()) {
        output_ += log.time + ' ' + std::to_string(Events::kOutLeft) + "\n";
        return;
    }
}

void Handler::EventInLeft(Log& log) {
    if (std::find(tables_.begin(), tables_.end(), log.body) == tables_.end() &&
        std::find(waiting_room_.begin(), waiting_room_.end(), log.body) == waiting_room_.end()) {
        output_ += log.time + ' ' + std::to_string(Events::kOutError) + " ClientUnknown\n";
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
    if (!waiting_room_.empty()) {
        tables_[i] = waiting_room_.back();
        output_ +=  log.time + ' ' + std::to_string(Events::kOutSatDown) + " " + 
                    waiting_room_.back() + " " + std::to_string(i + 1) +"\n";
        waiting_room_.pop_back();
    }
}


void Handler::EventLeftAll() {
    std::set<std::string> all;
    for (auto w : waiting_room_) {
        if (w == "") continue;
        all.insert(w);
    }
    for (auto t : tables_) {
        if (t == "") continue;
        all.insert(t);
    }
    for (auto s : all) {
        output_ += data_.end + " " + std::to_string(Events::kOutLeft) + " " + s + "\n"; 
    }
}

