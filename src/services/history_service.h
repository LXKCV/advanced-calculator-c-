#pragma once
#include "models/history_entry.h"
#include <vector>

class HistoryService {
public:
    void load();
    void save() const;
    void add(const HistoryEntry& e);
    const std::vector<HistoryEntry>& all() const { return entries_; }
private:
    std::vector<HistoryEntry> entries_;
};
