#include "settings_service.h"
#include <QDir>
#include <QFile>

QString SettingsService::path() const { return QDir::currentPath() + "/data/settings.json"; }
void SettingsService::load() {
    QFile f(path());
    if(!f.exists()) return;
    if(f.open(QIODevice::ReadOnly)) {
        data_ = nlohmann::json::parse(f.readAll().toStdString(), nullptr, false);
        if(data_.is_object()) {
            radians = data_.value("radians", true);
            soundEnabled = data_.value("soundEnabled", false);
            theme = QString::fromStdString(data_.value("theme", "themes/dark.qss"));
        }
    }
}
void SettingsService::save() const {
    nlohmann::json j{{"radians",radians},{"soundEnabled",soundEnabled},{"theme",theme.toStdString()}};
    QDir().mkpath("data");
    QFile f(path());
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)) f.write(QString::fromStdString(j.dump(2)).toUtf8());
}
