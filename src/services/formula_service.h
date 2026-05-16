#pragma once
#include <QString>
#include <vector>

struct FormulaNote { QString title, category, formula, notes; };
class FormulaService {
public:
    void load(); void save() const;
    void add(const FormulaNote& n); const std::vector<FormulaNote>& all() const { return notes_; }
private:
    std::vector<FormulaNote> notes_;
};
