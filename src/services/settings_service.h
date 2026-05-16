#pragma once
#include <QString>
#include <nlohmann/json.hpp>

class SettingsService {
public:
    void load();
    void save() const;
    bool radians{true};
    bool soundEnabled{false};
    QString theme{"themes/dark.qss"};
private:
    QString path() const;
    nlohmann::json data_;
};
