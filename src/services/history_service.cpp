#include "history_service.h"
#include <QDir>
#include <QFile>
#include <nlohmann/json.hpp>

void HistoryService::load() {
    QFile f(QDir::currentPath()+"/data/history.json");
    if(!f.exists()||!f.open(QIODevice::ReadOnly)) return;
    auto j=nlohmann::json::parse(f.readAll().toStdString(), nullptr, false);
    if(!j.is_array()) return;
    entries_.clear();
    for(auto &x:j) entries_.push_back({QString::fromStdString(x.value("expression","")),QString::fromStdString(x.value("result","")),QString::fromStdString(x.value("timestamp",""))});
}
void HistoryService::save() const {
    nlohmann::json j=nlohmann::json::array();
    for(auto &e:entries_) j.push_back({{"expression",e.expression.toStdString()},{"result",e.result.toStdString()},{"timestamp",e.timestamp.toStdString()}});
    QDir().mkpath("data");
    QFile f(QDir::currentPath()+"/data/history.json");
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)) f.write(QString::fromStdString(j.dump(2)).toUtf8());
}
void HistoryService::add(const HistoryEntry &e){ entries_.push_back(e); save(); }
