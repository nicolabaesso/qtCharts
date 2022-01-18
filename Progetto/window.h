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
#include <QComboBox>
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

    vector<QLabel*> idVector;
    vector<QLineEdit*> labelVector;
    vector<QLineEdit*> dataVector;
    QMenu* file;
    QMenu* chart;
    QPlainTextEdit* fileName;
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
    QPushButton* confirmNewFileButton;
    QPushButton* confirmDeleteDataButton;
    QPushButton* exitWarningButton;
    QPushButton* abortOperationButton;
    QDialog* newFileDialog;
    QDialog* warningDialog;
    QDialog* deleteDataDialog;
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
    void createChart(Chart *c);
    void showNewFileDialog();
    void deletePreviousChart();
    QString getNewFileName() const;
    void closeNewFileDialog();
    void closeDeleteDialog();
    void removeDataValues();
    void initExampleValues(DataHandler readedData);
    const vector<QLabel *> &getIdVector() const;

    const vector<QLineEdit *> &getLabelVector() const;
    const vector<QLineEdit *> &getDataVector() const;
    void showDeleteDataDialog();
    QString getDeleteDataComboBoxValue() const;
    void removeDeletedElement(int index);
private slots:
    void closeWarning();
    void abortOperation();
    void deleteData();
};
#endif // WINDOW_H
