#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QException>

class Exception: public QException{
public:
    void raise() const;
    Exception* clone() const;
};

#endif // EXCEPTION_H
