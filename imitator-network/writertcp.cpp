#include "writertcp.h"

WriterTcp::WriterTcp(int data_array_len) : WriterGeneral(data_array_len)
{
    cout << "WriterTcp created" << endl;
    moduleServer = new Server;
    connect(moduleServer, SIGNAL(sendInfo(int)),
            this,         SLOT(getInfo(int)));
}

WriterTcp::~WriterTcp()
{
    cout << "WriterTcp deleting" << endl;
    delete moduleServer;
}

void WriterTcp::newFrame()
{
    cout << "WriterTcp newFrame" << endl;
}

void WriterTcp::write(double angle, complex<double> *data)
{
    cout << "WriterTcp write" << endl;
    // Формирование HeaderString

}

void WriterTcp::stop_writing()
{
    cout << "WriterTcp stop_writing" << endl;
}

void WriterTcp::getInfo(int info)
{

    if (info == INFO_ALL_CONNECTED){
        QByteArray hello;
        QString message = "Greetings";
        QString who = "Imitator";
        QString when = QDateTime::currentDateTime().toString("hh:mm:ss");
        unsigned int size = message.toUtf8().size() + who.toUtf8().size() + when.toUtf8().size() + 3;
        hello.append(size >> 0);
        hello.append(size >> 8);
        hello.append(size >> 16);
        hello.append(size >> 24);
        hello.append(who.toLocal8Bit());
        hello.append('\0');
        hello.append(when.toLocal8Bit());
        hello.append('\0');
        hello.append(message.toLocal8Bit());
        hello.append('\0');
        moduleServer->sendToCli(&hello, SOCKET_ID_LOG);
    }

    emit sendInfo(info);
}
