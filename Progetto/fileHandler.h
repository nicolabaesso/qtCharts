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
    ~FileHandler();
    DataHandler& readFromFile(QString path="./example.xml");
    void saveFile();
    DataHandler& getReadedData();
    void clearData();
    void setReadedData(const DataHandler &newReadedData);
    const QString &getFileName() const;
    void setFileName(const QString &newFileName);
    void saveNewFile(QString path);
    void addData(Data d);
    void editData(Data d, int index);
    void deleteData(int index);
};

#endif // FILEHANDLER_H
