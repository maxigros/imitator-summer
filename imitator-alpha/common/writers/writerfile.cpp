#include "writerfile.h"

WriterFile::WriterFile()
{
    qDebug() << "WriterFile create";
}

WriterFile::~WriterFile()
{
    qDebug() << "WriterFile deleting";
    if (dataFile->isOpen())
        dataFile->close();
}

void WriterFile::write(double angle, complex<double> *data)
{
    qDebug() << "WriterFile write";
    header_string[8] = ((int)angle >> 8) & 0xFF;    // angle
    header_string[9] = ((int)angle >> 0) & 0xFF;    //
    int temp = (int)(QDateTime::currentSecsSinceEpoch());
    header_string[10] = (temp >> 24) & 0xFF;   // time
    header_string[11] = (temp >> 16) & 0xFF;   //
    header_string[12] = (temp >>  8) & 0xFF;   //
    header_string[13] = (temp >>  0) & 0xFF;   //

    // Собираем пакет для отправки
    bufferToWrite.append(header_string);

    for (int i = 0; i < sizeToSend; i++)
        bufferToWrite.append((char*)data + 2*sizeof(double)*i, 2*sizeof(double));

    dataFile->write(bufferToWrite.data(), bufferToWrite.size());
    dataFile->flush();

    bufferToWrite.clear();
}

void WriterFile::newFrame()
{
    qDebug() << "WriterFile newFrame";
    QByteArray t_data;
    t_data.append((frameSize >> 24) & 0xFF);
    t_data.append((frameSize >> 16) & 0xFF);
    t_data.append((frameSize >>  8) & 0xFF);
    t_data.append((frameSize >>  0) & 0xFF);
    dataFile->write(t_data.data(), t_data.size());
    dataFile->flush();
}

void WriterFile::stop_writing()
{

}

void WriterFile::get_ready(int data_array_len, int steps_in_frame, QString filename)
{
    if (!QDir("data").exists())
            QDir().mkdir("data");
    dataFile = new QFile();
    QStringList str_list = filename.split(".");
    dataFile->setFileName(QString("data/%1(%2).%3")
                          .arg(str_list[0])
                          .arg(QDateTime::currentDateTime().toString("hh:mm:ss_dd.MM.yyyy"))
                          .arg(str_list[1]));
    if (!dataFile->open(QFile::WriteOnly)){
        qDebug() << "WriterFile get_ready file error";
        return;
    }

    frameSize = (16 + 4 * data_array_len) * steps_in_frame;
    sizeToSend = data_array_len;

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

    header_string.append((sizeToSend >> 24) & 0xFF);  // 4
    header_string.append((sizeToSend >> 16) & 0xFF);  // 5
    header_string.append((sizeToSend >>  8) & 0xFF);  // 6
    header_string.append((sizeToSend >>  0) & 0xFF);  // 7
    unsigned short int angle = 0;
    header_string.append((angle >> 8) & 0xFF);    // 8
    header_string.append((angle >> 0) & 0xFF);    // 9
    unsigned short int sta_reserved = 0;
    header_string.append((sta_reserved >> 8) & 0xFF);    // 10
    header_string.append((sta_reserved >> 0) & 0xFF);    // 11
    unsigned int time = 0;
    header_string.append((time >> 24) & 0xFF);    // 12
    header_string.append((time >> 16) & 0xFF);    // 13
    header_string.append((time >>  8) & 0xFF);    // 14
    header_string.append((time >>  0) & 0xFF);    // 15

    newFrame();
    emit sendInfo(INFO_ALL_CONNECTED);
}
