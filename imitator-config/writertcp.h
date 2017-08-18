#ifndef WRITERTCP_H
#define WRITERTCP_H

#include "imitator_headers.h"
#include "writergeneral.h"
#include "server.h"

class WriterTcp : public WriterGeneral
{
    Q_OBJECT
public:
    explicit WriterTcp(int data_array_len);
    ~WriterTcp();

private:
    void newFrame();
    void write(double angle, complex<double> *data);
    void stop_writing();
    Server *moduleServer;

signals:
    void sendInfo(int info);
private slots:
    void getInfo(int info);
};

#endif // WRITERTCP_H
