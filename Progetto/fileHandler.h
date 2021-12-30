#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QtXml>
#include "dataHandler.h"
class FileHandler{
private:
    QDomDocument doc;
    DataHandler readedData;
    void initExampleFile();
public:
    FileHandler(DataHandler rd=DataHandler());
    ~FileHandler();
    void readFromFile(string name);
    void saveFile();
};

#endif // FILEHANDLER_H
