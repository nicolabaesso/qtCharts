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
#include <QChart>
#include <QChartView>
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

    Chart c;
    QMenu* file;
    QMenu* chart;

    QGridLayout* chartL;

    void initMenu(QVBoxLayout* mainLayout);

    void initDataLayout(QHBoxLayout* mainLayout);
    void initChartLayout(QHBoxLayout* mainLayout);

public:
    Window(QWidget *parent=nullptr);
    void showWarning(const QString& message);
    QString showSaveDialog();
    QString showOpenDialog();
    void setController(Controller* c);
    void updateChart(DataHandler d);
    void showChart(QChart* c);
    void createLineChart(DataHandler d);
signals:

};
#endif // WINDOW_H
