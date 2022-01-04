#ifndef MODEL_H
#define MODEL_H
#include "fileHandler.h"
#include "exception.h"
class Model{
private:
    FileHandler file;
public:
    Model();
    void readFile(QString path="./example.xml");
    void saveFile(QString path);
};

#endif // MODEL_H
