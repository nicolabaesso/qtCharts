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
    /*
    void showChart();
    void changeChart();
    void editData();*/
    void newFile();
    void openFile();
    void saveFile();

};


#endif // CONTROLLER_H
