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
#include <QLineEdit>
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

    vector<QLineEdit*> labelVector;
    vector<QLineEdit*> dataVector;
    QMenu* file;
    QMenu* chart;
    QPlainTextEdit* fileName;
    QChartView* chartViewer;
    QGridLayout* chartL;
    QGridLayout* dataL;
    QGridLayout* dialogLayout;
    QPushButton* addDataButton;
    QPushButton* saveDataButton;
    QPushButton* newFileButton;
    QPushButton* openFileButton;
    QPushButton* saveFileButton;
    QPushButton* loadBarChartButton;
    QPushButton* loadLineChartButton;
    QPushButton* loadPieChartButton;
    QPushButton* confirmNewFileButton;
    QPushButton* exitWarningButton;
    QDialog* newFileDialog;
    QDialog* warningDialog;
    QLineEdit* labelEdit;
    QLineEdit* dataEdit;
    QLabel* idData;
    QFrame* dataFrame;

    int rowGridLayoutData;
    int columnGridLayoutData;

    void initMenu(QHBoxLayout *mainLayout);

    void initDataLayout(QHBoxLayout* mainLayout);
    void initChartLayout(QHBoxLayout* mainLayout);

    void initToolBar(QHBoxLayout *mainLayout);

    void initVectors(DataHandler* readedData);
    void removeFromLayout(int row, int column);
    void initDataFrame(QFrame* dataFrame);

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
    void removeDataValues();
    void initExampleValues(DataHandler readedData);
private slots:
    void closeWarning();
};
#endif // WINDOW_H
