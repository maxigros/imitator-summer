#ifndef WRITERTCP_H
#define WRITERTCP_H

#include "../../../imitator/imitator_headers.h"
#include "server.h"
#include "../writergeneral.h"

class WriterTcp : public WriterGeneral
{
    Q_OBJECT
public:
    explicit WriterTcp();
    ~WriterTcp();

private:
    void newFrame();
    void write(double angle, complex<double> *data);
    void stop_writing();
    void get_ready(int data_array_len, int steps_in_frame);
    Server *moduleServer;
    // Буфер данных на отправку
    QByteArray bufferToSend;
    // Счетчик кадров в буфере на отправку
    int framesInBuffer = 0;

    // for debug
    int tempCounter1 = 0;
    int tempCounter2 = 0;

private slots:
    void getInfo(int info);
};

#endif // WRITERTCP_H
