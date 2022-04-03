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
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
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
    Chart* activeChart;
    vector<QLabel*> idVector;
    vector<QLineEdit*> labelVector;
    vector<QLineEdit*> dataVector;
    QMenu* file;
    QMenu* edit;
    QMenu* chart;
    QMenu* about;
    QLineEdit* fileName;
    QLineEdit* newTitle;
    QChartView* chartViewer;
    QGridLayout* chartL;
    QGridLayout* dataL;
    QPushButton* addDataButton;
    QPushButton* saveDataButton;
    QPushButton* deleteDataButton;
    QPushButton* newFileButton;
    QPushButton* openFileButton;
    QPushButton* saveFileButton;
    QPushButton* saveNewFileButton;
    QPushButton* loadBarChartButton;
    QPushButton* loadLineChartButton;
    QPushButton* loadPieChartButton;
    QPushButton* changeTitleButton;
    QPushButton* confirmNewFileButton;
    QPushButton* confirmDeleteDataButton;
    QPushButton* confirmNewTitleButton;
    QPushButton* exitWarningButton;
    QPushButton* abortOperationButton;
    QDialog* newFileDialog;
    QDialog* warningDialog;
    QDialog* deleteDataDialog;
    QDialog* changeTitleDialog;
    QLabel* idData;
    QFrame* dataFrame;
    QLabel* idInit;
    QLabel* labelInit;
    QLabel* valueInit;
    QComboBox* deleteDataComboBox;
    QFrame* oldDataFrame;
    QHBoxLayout* visualisationLayout;

    int rowGridLayoutData;
    int columnGridLayoutData;

    void initMenu(QHBoxLayout *mainLayout);
    void initDataLayout(QHBoxLayout* mainLayout);
    void initChartLayout(QHBoxLayout* mainLayout);
    void initToolBar(QHBoxLayout *mainLayout);
    void initVectors(DataHandler* readedData);
    void removeFromLayout(int row, int column);
    void initDataFrame(QFrame* dataFrame);
    void setDataConnect();
    void initDataId();

public:
    Window(QWidget *parent=nullptr);
    void showWarning(const QString& message);
    QString showSaveDialog();
    QString showOpenDialog();
    void setController(Controller* c);
    void initDataValues(DataHandler readedData);
    void updateChart(DataHandler d);
    void showChart(QChart* c);
    void createChart();
    void showNewFileDialog();
    void deletePreviousChart();
    QString getNewFileName() const;
    void closeNewFileDialog();
    void removeDataValues();
    void initExampleValues(DataHandler readedData);
    const vector<QLabel *> &getIdVector() const;
    void closeDeleteDialog();
    const vector<QLineEdit *> &getLabelVector() const;
    const vector<QLineEdit *> &getDataVector() const;
    void showDeleteDataDialog();
    QString getDeleteDataComboBoxValue() const;
    Chart *getChart() const;
    void setActiveChart(Chart *newActiveChart);
    Chart *getActiveChart() const;
    void showChangeTitleDialog();
    QString getNewTitle() const;
    void closeNewTitleDialog();
    void checkDataLabel();

private slots:
    void closeWarning();
    void abortOperation();
    void deleteData();
    void abortNewFile();
    void abortChangeTitle();
    void abortDeleteData();
    void showInfo();
};
#endif // WINDOW_H
