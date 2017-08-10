#include "boxnetwork.h"

BoxNetwork::BoxNetwork(QString writer_mode, QObject *parent) : QObject(parent)
{
    if (!writer_mode.compare(QString::fromUtf8("Передача по сети"))){
        configWriterMode = WRITER_MODE_NETWORK;
        cout << "BoxNetwork created with mode: Передача по сети" << endl;
    }
    if (!writer_mode.compare(QString::fromUtf8("Запись в файл"))){
        configWriterMode = WRITER_MODE_FILE;
        cout << "BoxNetwork created with mode: Запись в файл" << endl;
    }


}

BoxNetwork::~BoxNetwork()
{
    cout << "BoxNetwork deleting" << endl;
}

void BoxNetwork::stop_box()
{
    cout << "BoxNetwork stopping" << endl;
    toStop = true;
    emit finish();
}

void BoxNetwork::process()
{
    cout << "BoxNetwork processing" << endl;
    // Ожидаем параметров, после этого создаем класс с интерфейсами
    while(waiting_for_info && !toStop);

    if (!toStop){
        cout << "BoxNetwork process обработка параметров" << endl;
        switch (configWriterMode) {
        case WRITER_MODE_NETWORK:
            writer = new WriterTcp(data_array_len);
            connect(this, SIGNAL(finish()), writer, SLOT(deleteLater()));
            break;
        case WRITER_MODE_FILE:
            break;
        default:
            break;
        }
    }
}

void BoxNetwork::getConfigParams(QMap<QString, double> params)
{
    // Проверяем, пришел ли нужный параметр
    if (params.keys().contains("PARAM_DATA_ARRAY_LEN")){
        data_array_len = params.value("PARAM_DATA_ARRAY_LEN");
        waiting_for_info = false;
        cout << "BoxNetwork getConfigParams успех" << endl;
        return;
    }

    // Ошибка: нужного параметра нет
    cout << "BoxNetwork getConfigParams ошибка: нужного параметра нет" << endl;
    // ToDo: обработка ошибки (м.б. сигналы)

}

void BoxNetwork::getData(int data_type, double angle, complex<double> *data)
{
    if (waiting_for_info){
        // Ошибка: конфигурация не завершена, не можем работать с данными
        cout << "BoxNetwork getData ошибка: конфигурация не завершена" << endl;
        // ToDo: обработка ошибки (м.б. сигналы)
        return;
    }

    cout << "BoxNetwork getData успех: конфигурация завершена" << endl;
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
        cout << "BoxNetwork getData ошибка: неизвестный тип данных" << endl;
        break;
    }
}

