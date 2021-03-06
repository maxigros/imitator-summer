#include "writergeneral.h"

WriterGeneral::WriterGeneral(int data_array_len, QObject *parent) : QObject(parent)
{
    qDebug() << "WriterGeneral created";
}

WriterGeneral::~WriterGeneral()
{
    qDebug() << "WriterGeneral deleting";
}

void WriterGeneral::i_newFrame()
{
    newFrame();
}

void WriterGeneral::i_write(double angle, complex<double> *data)
{
    write(angle, data);
}

void WriterGeneral::i_stop_writing()
{
    stop_writing();
}

void WriterGeneral::newFrame()
{

}

void WriterGeneral::write(double angle, complex<double> *data)
{
    qDebug() << "WriterGeneral write";
    Q_UNUSED(angle);
    Q_UNUSED(data);
}

void WriterGeneral::stop_writing()
{

}
