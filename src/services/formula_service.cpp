#include "formula_service.h"
#include <QDir>
#include <QFile>
#include <nlohmann/json.hpp>

void FormulaService::load(){
    QFile f(QDir::currentPath()+"/data/formulas.json"); if(!f.exists()||!f.open(QIODevice::ReadOnly)) return;
    auto j=nlohmann::json::parse(f.readAll().toStdString(), nullptr, false); if(!j.is_array()) return; notes_.clear();
    for(auto &x:j) notes_.push_back({QString::fromStdString(x.value("title","")),QString::fromStdString(x.value("category","General")),QString::fromStdString(x.value("formula","")),QString::fromStdString(x.value("notes",""))});
}
void FormulaService::save() const {
    nlohmann::json j=nlohmann::json::array(); for(auto &n:notes_) j.push_back({{"title",n.title.toStdString()},{"category",n.category.toStdString()},{"formula",n.formula.toStdString()},{"notes",n.notes.toStdString()}});
    QDir().mkpath("data"); QFile f(QDir::currentPath()+"/data/formulas.json"); if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)) f.write(QString::fromStdString(j.dump(2)).toUtf8());
}
void FormulaService::add(const FormulaNote &n){ notes_.push_back(n); save(); }
