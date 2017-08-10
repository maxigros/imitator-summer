#include "writertcp.h"

WriterTcp::WriterTcp(int data_array_len) : WriterGeneral(data_array_len)
{
    cout << "WriterTcp created" << endl;
}

WriterTcp::~WriterTcp()
{
    cout << "WriterTcp deleting" << endl;
}
