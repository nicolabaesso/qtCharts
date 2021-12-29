#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QtXml>
#include "dataHandler.h"
class FileHandler{
private:
    QDomDocument doc;
    DataHandler readedData;
public:
    FileHandler();
    void readFromFile(string name);
    void initExampleFile();
    void saveFile();
};

#endif // FILEHANDLER_H
