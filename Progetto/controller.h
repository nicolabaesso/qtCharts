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

signals:
};


#endif // CONTROLLER_H
