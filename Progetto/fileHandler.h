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
    DataHandler& readFromFile(QString path="./example.xml");
    void saveFile(QString path);
    DataHandler& getReadedData();
    void clearData();
};

#endif // FILEHANDLER_H
