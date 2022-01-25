#ifndef MODEL_H
#define MODEL_H
#include "fileHandler.h"
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
    void setTitle(QString title);
};

#endif // MODEL_H
