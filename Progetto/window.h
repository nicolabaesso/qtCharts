#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QChart>
#include <QChartView>
#include <QDialogButtonBox>
#include <QPushButton>
#include "chart.h"
#include "lineChart.h"
#include "pieChart.h"
#include "barChart.h"

using QtCharts::QChart;
using QtCharts::QChartView;

class Controller;

class Window: public QWidget{
  Q_OBJECT
private:
    Controller* controller;

    Chart* c;

    QMenu* file;
    QMenu* chart;
    QPlainTextEdit* fileName;
    QChartView* chartViewer;
    QGridLayout* chartL;

    void initMenu(QVBoxLayout* mainLayout);

    void initDataLayout(QHBoxLayout* mainLayout);
    void initChartLayout(QHBoxLayout* mainLayout);

    void initChart();

public:
    Window(QWidget *parent=nullptr);
    void showWarning(const QString& message);
    QString showSaveDialog();
    QString showOpenDialog();
    void setController(Controller* c);
    void updateChart(DataHandler d);
    void showChart(QChart* c);
    void createChart(Chart *c);
    QString showNewFileDialog(DataHandler& d);
    void deletePreviousChart();
signals:

};
#endif // WINDOW_H
