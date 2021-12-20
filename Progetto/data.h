#ifndef DATA_H
#define DATA_H
#include <iostream>
using std::string;
class Data{
private:
    string label;
    double data;
public:
    Data(string l="default",double d=0);
    ~Data();
    string getLabel() const;
    double getData() const;
    void setLabel(string l);
    void setData(double d);
};
#endif // DATA_H
