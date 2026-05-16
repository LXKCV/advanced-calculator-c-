#pragma once

#include <QApplication>
#include <memory>

class MainWindow;
class SettingsService;
class HistoryService;
class FormulaService;

class CalculatorApplication {
public:
    CalculatorApplication(int &argc, char **argv);
    int run();

private:
    QApplication app_;
    std::unique_ptr<SettingsService> settings_;
    std::unique_ptr<HistoryService> history_;
    std::unique_ptr<FormulaService> formulas_;
    std::unique_ptr<MainWindow> mainWindow_;
};
