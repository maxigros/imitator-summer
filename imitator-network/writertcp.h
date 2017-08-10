#ifndef WRITERTCP_H
#define WRITERTCP_H

#include "imitator_headers.h"
#include "writergeneral.h"

class WriterTcp : public WriterGeneral
{
    Q_OBJECT
public:
    explicit WriterTcp(int data_array_len);
    ~WriterTcp();
};

#endif // WRITERTCP_H
