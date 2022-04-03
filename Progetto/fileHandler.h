#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QtXml>
#include "dataHandler.h"
class FileHandler{
private:
    QString fileName;
    DataHandler readedData;
    void initExampleFile();
public:
    FileHandler(DataHandler rd=DataHandler());
    ~FileHandler()=default;
    DataHandler& readFromFile(const QString& path="./example.xml");
    void saveFile();
    DataHandler& getReadedData();
    void clearData();
    void setReadedData(const DataHandler& newReadedData);
    void setFileName(const QString& newFileName);
    void addData(const Data& d);
    void editData(const Data& d, const int& index);
    void deleteData(const int& index);
    void setTitle(const QString& title);
};

#endif // FILEHANDLER_H
