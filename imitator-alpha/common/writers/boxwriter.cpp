#include "boxwriter.h"

BoxWriter::BoxWriter(QString writer_mode, QObject *parent) : QObject(parent)
{
    if (!writer_mode.compare(QString::fromUtf8("Передача по сети"))){
        configWriterMode = WRITER_MODE_NETWORK;
    }
    if (!writer_mode.compare(QString::fromUtf8("Запись в файл"))){
        configWriterMode = WRITER_MODE_FILE;
    }
}

BoxWriter::~BoxWriter()
{

}

void BoxWriter::stop_box()
{
    toStop = true;
    emit finish();
}

void BoxWriter::process()
{
    // Ожидаем параметров, после этого создаем класс с интерфейсами
    while(waitingForConfigInfo && !toStop);

    if (!toStop){
        qDebug() << "BoxWriter::process success: config applied";
        switch (configWriterMode) {
        case WRITER_MODE_NETWORK:
            writer = new WriterTcp();
            writer->i_get_ready(dataArrayLength, thinStepsInFrame);
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

void BoxWriter::getConfigParams(Storage *configParams)
{
    // Проверка чтения параметров
//    for (int i = 0; i < configParams->parameters.simple.keys().count(); i++)
//        qDebug() << QString("       %1 : %2")
//                    .arg(configParams->parameters.simple.keys().at(i))
//                    .arg(configParams->parameters.simple.value(configParams->parameters.simple.keys().at(i)));

//    qDebug() << "   TARGETS:";
//    for (int i = 0; i < configParams->parameters.targets.count(); i++){
//        for (int j = 0; j < configParams->parameters.targets[i].keys().count(); j++)
//            qDebug() << QString("        %1 : %2")
//                        .arg(configParams->parameters.targets[i].keys().at(j))
//                        .arg(configParams->parameters.targets[i].value(configParams->parameters.targets[i].keys().at(j)));
//        qDebug() << "\r\n";
//    }

    // Проверяем, пришел ли нужный параметр
    if (configParams->parameters.simple.keys().contains("PULSE_REPEAT_TIME") &&
        configParams->parameters.simple.keys().contains("FREQUENCY") &&
        configParams->parameters.simple.keys().contains("LOCATOR_ENCODER_RESOLUTION") &&
        configParams->parameters.simple.keys().contains("THINNING")){

        dataArrayLength = (int)(configParams->parameters.simple.value("PULSE_REPEAT_TIME")/
                               (1 / configParams->parameters.simple.value("FREQUENCY")));
        dataArrayLength = 20;
        maxStepsInFrame = (int)configParams->parameters.simple.value("LOCATOR_ENCODER_RESOLUTION");
        stepSizeWithThinning = configParams->parameters.simple.value("THINNING");
        thinStepsInFrame = (int)(maxStepsInFrame / stepSizeWithThinning);
        waitingForConfigInfo = false;
        return;
    }

    // Ошибка: нужного параметра нет
    if (!configParams->parameters.simple.keys().contains("PULSE_REPEAT_TIME"))
        qDebug() << "BoxWriter::getConfigParams error: parameter 'PULSE_REPEAT_TIME' is absent";
    if (!configParams->parameters.simple.keys().contains("FREQUENCY"))
        qDebug() << "BoxWriter::getConfigParams error: parameter 'FREQUENCY' is absent";
    if (!configParams->parameters.simple.keys().contains("LOCATOR_ENCODER_RESOLUTION"))
        qDebug() << "BoxWriter::getConfigParams error: parameter 'LOCATOR_ENCODER_RESOLUTION' is absent";
    if (!configParams->parameters.simple.keys().contains("THINNING"))
        qDebug() << "BoxWriter::getConfigParams error: parameter 'THINNING' is absent";
    // ToDo: обработка ошибки (м.б. сигналы)

}

void BoxWriter::getData(int data_type, double angle, complex<double> *data)
{
    if (waitingForConfigInfo){
        // Ошибка: конфигурация не завершена, не можем работать с данными
        qDebug() << "BoxWriter::getData error: config not finished";
        // ToDo: обработка ошибки (м.б. сигналы)
        return;
    }

//    qDebug() << "BoxWriter getData успех: конфигурация завершена";
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
        qDebug()<< "BoxWriter::getData error: unknown data type";
        break;
    }
}

void BoxWriter::getInfo(int info)
{
    switch (info) {
    case INFO_ALL_CONNECTED:
        emit sendInfo(INFO_ALL_CONNECTED);
        break;
    case INFO_SERVER_FINISHED:
        stop_box();
        break;
    default:
        qDebug() << "BoxWriter::getInfo error: unknown info ID";
        break;
    }
}

