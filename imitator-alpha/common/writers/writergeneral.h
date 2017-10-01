#ifndef WRITERGENERAL_H
#define WRITERGENERAL_H

#include "../../imitator/imitator_headers.h"

class WriterGeneral : public QObject
{
    Q_OBJECT
public:
    explicit WriterGeneral(QObject *parent = 0);
    ~WriterGeneral();

public:
    // Интерфейсы:
    void i_newFrame();
    void i_write(double angle, complex<double> *data);
    void i_stop_writing();
    void i_get_ready(int data_array_len, int steps_in_frame);
protected:
    QByteArray header_string;
    int sizeToSend;
    // Переопределяются в наследниках:
    virtual void newFrame();
    virtual void write(double angle, complex<double> *data);
    virtual void stop_writing();
    virtual void get_ready(int data_array_len, int steps_in_frame);  
signals:
    void sendInfo(int info);
};

#endif // WRITERGENERAL_H
