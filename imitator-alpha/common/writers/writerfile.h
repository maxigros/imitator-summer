#ifndef WRITERFILE_H
#define WRITERFILE_H

#include "../../imitator/imitator_headers.h"
#include "writergeneral.h"

class WriterFile : public WriterGeneral
{
    Q_OBJECT
public:
    explicit WriterFile();
    ~WriterFile();

private:
    QFile *dataFile;
    QByteArray bufferToWrite;
    int frameSize;

    void write(double angle, complex<double> *data);
    void newFrame();
    void stop_writing();
    void get_ready(int data_array_len, int steps_in_frame, QString filename = "data_drop.bin");
};

#endif // WRITERFILE_H
