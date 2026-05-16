#include "application.h"
#include "services/settings_service.h"
#include "services/history_service.h"
#include "services/formula_service.h"
#include "ui/views/main_window.h"
#include <QTimer>

CalculatorApplication::CalculatorApplication(int &argc, char **argv) : app_(argc, argv) {
    app_.setApplicationName("Advanced Calculator");
    app_.setOrganizationName("Acme");

    settings_ = std::make_unique<SettingsService>();
    history_ = std::make_unique<HistoryService>();
    formulas_ = std::make_unique<FormulaService>();

    settings_->load();
    history_->load();
    formulas_->load();

    mainWindow_ = std::make_unique<MainWindow>(*settings_, *history_, *formulas_);
}

int CalculatorApplication::run() {
    mainWindow_->show();
    QTimer::singleShot(0, [this] { mainWindow_->playStartupAnimation(); });
    return app_.exec();
}
