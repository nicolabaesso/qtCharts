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

    vector<QPlainTextEdit> labelVector;
    vector<QPlainTextEdit> dataVector;
    QMenu* file;
    QMenu* chart;
    QPlainTextEdit* fileName;
    QChartView* chartViewer;
    QGridLayout* chartL;
    QGridLayout* dataL;
    QGridLayout* dialogLayout;
    QPushButton* addDataButton;
    QPushButton* newFileButton;
    QPushButton* openFileButton;
    QPushButton* saveFileButton;
    QPushButton* loadBarChartButton;
    QPushButton* loadLineChartButton;
    QPushButton* loadPieChartButton;
    QPushButton* confirmNewFileButton;
    QDialog* newFileDialog;

    int rowGridLayoutData;
    int columnGridLayoutData;

    void initMenu(QHBoxLayout *mainLayout);

    void initDataLayout(QHBoxLayout* mainLayout);
    void initChartLayout(QHBoxLayout* mainLayout);

    void initToolBar(QHBoxLayout *mainLayout);

   // void initVectors(DataHandler readedData);
public:
    Window(QWidget *parent=nullptr);
    void showWarning(const QString& message);
    QString showSaveDialog();
    QString showOpenDialog();
    void setController(Controller* c);
    void initDataValues(DataHandler readedData);
    void updateChart(DataHandler d);
    void showChart(QChart* c);
    void createChart(Chart *c);
    void showNewFileDialog();
    void deletePreviousChart();
    QString getNewFileName();
    void closeNewFileDialog();
};
#endif // WINDOW_H
