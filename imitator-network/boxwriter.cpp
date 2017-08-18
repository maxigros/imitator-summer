#include "boxwriter.h"

BoxWriter::BoxWriter(QString writer_mode, QObject *parent) : QObject(parent)
{
    if (!writer_mode.compare(QString::fromUtf8("Передача по сети"))){
        configWriterMode = WRITER_MODE_NETWORK;
        cout << "BoxWriter created with mode: Передача по сети" << endl;
    }
    if (!writer_mode.compare(QString::fromUtf8("Запись в файл"))){
        configWriterMode = WRITER_MODE_FILE;
        cout << "BoxWriter created with mode: Запись в файл" << endl;
    }


}

BoxWriter::~BoxWriter()
{
    cout << "BoxWriter deleting" << endl;
}

void BoxWriter::stop_box()
{
    cout << "BoxWriter stopping" << endl;
    toStop = true;
    emit finish();
}

void BoxWriter::process()
{
    cout << "BoxWriter processing" << endl;
    // Ожидаем параметров, после этого создаем класс с интерфейсами
    while(waiting_for_info && !toStop);

    if (!toStop){
        cout << "BoxWriter process обработка параметров" << endl;
        switch (configWriterMode) {
        case WRITER_MODE_NETWORK:
            writer = new WriterTcp(data_array_len);
            connect(this,   SIGNAL(finish()),
                    writer, SLOT(deleteLater()));
            connect(writer, SIGNAL(sendInfo(int)),
                    this,   SLOT(getInfo(int)));
            break;
        case WRITER_MODE_FILE:
            break;
        default:
            break;
        }
    }
}

void BoxWriter::getConfigParams(QMap<QString, double> params)
{
    // Проверяем, пришел ли нужный параметр
    if (params.keys().contains("PARAM_DATA_ARRAY_LEN")){
        data_array_len = params.value("PARAM_DATA_ARRAY_LEN");
        waiting_for_info = false;
        cout << "BoxWriter getConfigParams успех" << endl;
        return;
    }

    // Ошибка: нужного параметра нет
    cout << "BoxWriter getConfigParams ошибка: нужного параметра нет" << endl;
    // ToDo: обработка ошибки (м.б. сигналы)

}

void BoxWriter::getData(int data_type, double angle, complex<double> *data)
{
    if (waiting_for_info){
        // Ошибка: конфигурация не завершена, не можем работать с данными
        cout << "BoxWriter getData ошибка: конфигурация не завершена" << endl;
        // ToDo: обработка ошибки (м.б. сигналы)
        return;
    }

//    cout << "BoxWriter getData успех: конфигурация завершена" << endl;
    switch (data_type) {
    case DATA_TYPE_NEW_FRAME:
        writer->i_newFrame();
        break;
    case DATA_TYPE_WRITE:
        writer->i_write(angle, data);
        break;
    case DATA_TYPE_STOP_WRITING:
        writer->i_stop_writing();
        break;
    default:
        // Ошибка: неизвестный тип данных
        cout << "BoxWriter getData ошибка: неизвестный тип данных" << endl;
        break;
    }
}

void BoxWriter::getInfo(int info)
{
    switch (info) {
    case INFO_ALL_CONNECTED:
        cout << "BoxWriter getInfo ALL_CONNECTED" << endl;
        emit sendInfo(INFO_ALL_CONNECTED);
        break;
    case INFO_SERVER_FINISHED:
        cout << "BoxWriter getInfo SERVER_FINISHED" << endl;
        stop_box();
        break;
    default:
        cout << "BoxWriter getInfo unknown value" << endl;
        break;
    }
}

