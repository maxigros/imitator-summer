#include "writertcp.h"

WriterTcp::WriterTcp() : WriterGeneral()
{
    moduleServer = new Server;
    connect(moduleServer, SIGNAL(sendInfo(int)),
            this,         SLOT(getInfo(int)));
    moduleServer->start();
}

WriterTcp::~WriterTcp()
{
    delete moduleServer;
}

void WriterTcp::newFrame()
{
    qDebug() << "WriterTcp newFrame";
}

void WriterTcp::write(double angle, complex<double> *data)
{
//    qDebug() << "WriterTcp write";
    header_string[8] = ((int)angle >> 8) & 0xFF;    // angle
    header_string[9] = ((int)angle >> 0) & 0xFF;    //
    int temp = (int)(QDateTime::currentSecsSinceEpoch());
    header_string[10] = (temp >> 24) & 0xFF;   // time
    header_string[11] = (temp >> 16) & 0xFF;   //
    header_string[12] = (temp >>  8) & 0xFF;   //
    header_string[13] = (temp >>  0) & 0xFF;   //

    // Собираем пакет для отправки
    bufferToSend.append(header_string);

    for (int i = 0; i < sizeToSend; i++)
        bufferToSend.append((char*)data + 2*sizeof(double)*i, 2*sizeof(double));

//    delete [] data;

    framesInBuffer++;

    qDebug() << QString("Frame %1").arg(QString::number(tempCounter1++));

    if (framesInBuffer > 150){
        int t = bufferToSend.size();
        bufferToSend[0] = (t >> 24) & 0xFF;
        bufferToSend[1] = (t >> 16) & 0xFF;
        bufferToSend[2] = (t >>  8) & 0xFF;
        bufferToSend[3] = (t >>  0) & 0xFF;

        moduleServer->sendToCli(&bufferToSend, SOCKET_ID_DATA);
        framesInBuffer = 0;
        qDebug() << QString("Package %1").arg(QString::number(tempCounter2++));
        qDebug() << QString("Buffer size %1").arg(QString::number(bufferToSend.size()));
        tempCounter1 = 0;
        bufferToSend.clear();
    }

}

void WriterTcp::stop_writing()
{
    qDebug() << "WriterTcp stop_writing";
}

void WriterTcp::get_ready(int data_array_len, int steps_in_frame)
{
    bufferToSend.append((char*)(0), sizeof(int));     // reserved for buffer size
    sizeToSend = data_array_len;
    Q_UNUSED(steps_in_frame);
    // Header String
    /*
     * self.header_string = '{flags}{start_type}{reserved0}{reserved1}{data_size}{angle}{sta_reserved}{time}'.format(
            flags=struct.pack('B', 36),
            start_type=struct.pack('B', 0),
            reserved0=struct.pack('B', 0),
            reserved1=struct.pack('B', 0),
            data_size=struct.pack('I', receive_array_len),
            angle='{angle}',
            sta_reserved=struct.pack('H', 0),
            time='{time}',
        )
     */
    char t1 = 36;
    char t2 = 0;
    header_string.append(QByteArray::fromRawData(&t1, sizeof(char)));   // flags
    header_string.append(QByteArray::fromRawData(&t2, sizeof(char)));   // start_type
    header_string.append(QByteArray::fromRawData(&t2, sizeof(char)));   // reserved0
    header_string.append(QByteArray::fromRawData(&t2, sizeof(char)));   // reserved1
    // data_size
    header_string.append((sizeToSend >> 24) & 0xFF);  // 4
    header_string.append((sizeToSend >> 16) & 0xFF);  // 5
    header_string.append((sizeToSend >>  8) & 0xFF);  // 6
    header_string.append((sizeToSend >>  0) & 0xFF);  // 7
    // angle
    unsigned short int angle = 0;
    header_string.append((angle >> 8) & 0xFF);    // 8
    header_string.append((angle >> 0) & 0xFF);    // 9
    // sta_reserved
    unsigned short int sta_reserved = 0;
    header_string.append((sta_reserved >> 8) & 0xFF);    // 10
    header_string.append((sta_reserved >> 0) & 0xFF);    // 11
    // time
    unsigned int time = 0;
    header_string.append((time >> 24) & 0xFF);    // 12
    header_string.append((time >> 16) & 0xFF);    // 13
    header_string.append((time >>  8) & 0xFF);    // 14
    header_string.append((time >>  0) & 0xFF);    // 15
}

void WriterTcp::getInfo(int info)
{

    if (info == INFO_ALL_CONNECTED){
        QByteArray hello;
        QString message = "Greetings";
        QString who = " Imitator";
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
