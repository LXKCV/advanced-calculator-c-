#include "main_window.h"
#include "services/settings_service.h"
#include "services/history_service.h"
#include "services/formula_service.h"
#include <QChartView>
#include <QDateTime>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QShortcut>
#include <QStackedWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QPropertyAnimation>
using namespace QtCharts;

MainWindow::MainWindow(SettingsService& s, HistoryService& h, FormulaService& f):settings_(s),history_(h),formulas_(f){
    resize(1200,760);
    auto central=new QWidget; auto root=new QHBoxLayout(central);
    auto nav=new QVBoxLayout; auto sidebar=new QWidget; sidebar->setObjectName("sidebar"); sidebar->setLayout(nav);
    pages_=new QStackedWidget;
    QStringList labels={"Calculator","Programmer","Converter","Notes","History"};
    for(int i=0;i<labels.size();++i){ auto b=new QPushButton(labels[i]); nav->addWidget(b); connect(b,&QPushButton::clicked,this,[this,i]{ pages_->setCurrentIndex(i);}); }
    nav->addStretch();
    pages_->addWidget(buildBasicScientificPage()); pages_->addWidget(buildProgrammerPage()); pages_->addWidget(buildConverterPage()); pages_->addWidget(buildNotesPage()); pages_->addWidget(buildHistoryPage());
    root->addWidget(sidebar,1); root->addWidget(pages_,5); setCentralWidget(central);
    applyTheme();
}

QWidget* MainWindow::buildBasicScientificPage(){
    auto w=new QWidget; auto l=new QVBoxLayout(w);
    expression_=new QLineEdit; preview_=new QLabel("Real-time preview"); result_=new QLabel("0");
    auto evalBtn=new QPushButton("=");
    l->addWidget(new QLabel("Expression")); l->addWidget(expression_); l->addWidget(preview_); l->addWidget(result_); l->addWidget(evalBtn);
    auto chart=new QChart; auto series=new QLineSeries;
    for(double x=-6;x<=6;x+=0.2) series->append(x,std::sin(x));
    chart->addSeries(series); chart->createDefaultAxes(); l->addWidget(new QChartView(chart));
    connect(expression_,&QLineEdit::textChanged,this,[this](const QString &t){ auto r=parser_.evaluate(t.toStdString(),settings_.radians); preview_->setText(r.ok?QString::number(r.value):QString::fromStdString(r.error));});
    connect(evalBtn,&QPushButton::clicked,this,[this]{ auto r=parser_.evaluate(expression_->text().toStdString(),settings_.radians); if(r.ok){ result_->setText(QString::number(r.value)); history_.add({expression_->text(),QString::number(r.value),QDateTime::currentDateTime().toString(Qt::ISODate)});} else result_->setText(QString::fromStdString(r.error));});
    new QShortcut(QKeySequence(Qt::Key_Return), expression_, [evalBtn]{ evalBtn->click();});
    return w;
}
QWidget* MainWindow::buildProgrammerPage(){ auto w=new QWidget; auto l=new QVBoxLayout(w); l->addWidget(new QLabel("Programmer Mode: binary/hex/oct/dec + bitwise ready architecture")); return w; }
QWidget* MainWindow::buildConverterPage(){ auto w=new QWidget; auto l=new QVBoxLayout(w); l->addWidget(new QLabel("Unit Converter categories: length, weight, temperature, speed, data size, volume, time, energy + currency provider interface.")); return w; }
QWidget* MainWindow::buildNotesPage(){ auto w=new QWidget; auto l=new QVBoxLayout(w); notesEditor_=new QTextEdit; auto save=new QPushButton("Save Formula Note"); l->addWidget(new QLabel("Math Notes (Markdown-like)")); l->addWidget(notesEditor_); l->addWidget(save); connect(save,&QPushButton::clicked,this,[this]{ formulas_.add({"Untitled","General",notesEditor_->toPlainText(),""}); }); return w; }
QWidget* MainWindow::buildHistoryPage(){ auto w=new QWidget; auto l=new QVBoxLayout(w); historyList_=new QListWidget; for(auto &e:history_.all()) historyList_->addItem(e.timestamp+" | "+e.expression+" = "+e.result); l->addWidget(historyList_); return w; }

void MainWindow::applyTheme(){ QFile f(settings_.theme); if(f.open(QIODevice::ReadOnly)) setStyleSheet(f.readAll()); }
void MainWindow::playStartupAnimation(){ auto eff=new QGraphicsOpacityEffect(this); centralWidget()->setGraphicsEffect(eff); auto anim=new QPropertyAnimation(eff,"opacity",this); anim->setDuration(450); anim->setStartValue(0.0); anim->setEndValue(1.0); anim->start(QAbstractAnimation::DeleteWhenStopped); }
