#ifndef MODEL_H
#define MODEL_H
#include "fileHandler.h"
#include "exception.h"
class Model{
private:
    FileHandler file;
public:
    Model();
    DataHandler& readFile(QString path="./example.xml");
    void saveFile();
    DataHandler& getData();
    DataHandler& readExampleFile(QString path="./example.xml");
    void setData(DataHandler d);
    void saveNewFile(QString path);
    void editData(DataHandler dh);
    void deleteData(int index);
};

#endif // MODEL_H
