#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "window.h"
#include "model.h"

class Controller: public QObject{
    Q_OBJECT
private:
    Window* view;
    Model* model;
public:
    Controller(QObject* parent=nullptr);
    void setView(Window* newView);
    void setModel(Model* newModel);
    void loadExampleFile();


public slots:
    void changeTitle();
    void deleteData();
    void addData();
    void saveData();
    void newFile();
    void manageNewFile();
    void openFile();
    void saveFile();
    void loadLineChart();
    void loadPieChart();
    void loadBarChart();
    void saveNewFile();
    void manageChangeTitle();
};


#endif // CONTROLLER_H
