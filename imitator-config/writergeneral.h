#ifndef WRITERGENERAL_H
#define WRITERGENERAL_H

#include "imitator_headers.h"

class WriterGeneral : public QObject
{
    Q_OBJECT
public:
    explicit WriterGeneral(int data_array_len, QObject *parent = 0);
    ~WriterGeneral();

public:
    // Интерфейсы:
    void i_newFrame();
    void i_write(double angle, complex<double> *data);
    void i_stop_writing();
protected:
    // Переопределяются в наследниках:
    virtual void newFrame();
    virtual void write(double angle, complex<double> *data);
    virtual void stop_writing();

};

#endif // WRITERGENERAL_H
