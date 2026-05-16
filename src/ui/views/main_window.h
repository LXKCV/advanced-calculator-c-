#pragma once
#include <QMainWindow>
#include "core/expression_parser.h"

class QLineEdit; class QLabel; class QListWidget; class QStackedWidget; class QTextEdit;
class SettingsService; class HistoryService; class FormulaService;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(SettingsService&, HistoryService&, FormulaService&);
    void playStartupAnimation();
private:
    QWidget* buildBasicScientificPage();
    QWidget* buildProgrammerPage();
    QWidget* buildConverterPage();
    QWidget* buildNotesPage();
    QWidget* buildHistoryPage();
    void applyTheme();

    SettingsService& settings_; HistoryService& history_; FormulaService& formulas_;
    ExpressionParser parser_;
    QStackedWidget* pages_{nullptr};
    QLineEdit* expression_{nullptr}; QLabel* preview_{nullptr}; QLabel* result_{nullptr};
    QListWidget* historyList_{nullptr}; QTextEdit* notesEditor_{nullptr};
};
