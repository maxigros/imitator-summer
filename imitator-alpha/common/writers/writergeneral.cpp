#include "writergeneral.h"

WriterGeneral::WriterGeneral(QObject *parent) : QObject(parent)
{

}

WriterGeneral::~WriterGeneral()
{

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

void WriterGeneral::i_get_ready(int data_array_len, int steps_in_frame)
{
    get_ready(data_array_len, steps_in_frame);
}

void WriterGeneral::newFrame()
{

}

void WriterGeneral::write(double angle, complex<double> *data)
{

    Q_UNUSED(angle);
    Q_UNUSED(data);
}

void WriterGeneral::stop_writing()
{

}

void WriterGeneral::get_ready(int data_array_len, int steps_in_frame)
{
    Q_UNUSED(data_array_len);
    Q_UNUSED(steps_in_frame);
}
