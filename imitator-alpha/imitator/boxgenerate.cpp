#include "boxgenerate.h"

BoxGenerate::BoxGenerate(QString configFilename, QObject *parent) : QObject(parent)
{
    filename = configFilename;
    params = new Storage();
    connect(params, SIGNAL(sendInfo(int)), this, SLOT(getInfo(int)));
    connect(this, SIGNAL(finish()), params, SLOT(deleteLater()));

    imitator = new DataSource();
    connect(this, SIGNAL(finish()), imitator, SLOT(deleteLater()));
}

BoxGenerate::~BoxGenerate()
{

}

void BoxGenerate::stop()
{
    toStop = true;
    emit finish();
}

void BoxGenerate::process()
{
    params->process(filename);
    // Отправляем в BoxWriter
    emit sendConfigParams(params);
    // Конфигурация DataSource
    imitator->configure(params);
}

void BoxGenerate::getInfo(int info)
{
    switch (info) {
    case INFO_ALL_CONNECTED:
        run();
        break;
    case INFO_CONFIG_ERROR:
        stop();
        break;
    default:
        qDebug() << "BoxGenerate::getInfo error: unknown info ID";
        break;
    }
}

void BoxGenerate::run()
{
    /**************************************************************************
     * Generation
     *
     * Один проход WHILE - это один кадр. Обзоры формируются сменой угловых
     * направлений внутри класса, как и поворот локатора и движение целей
     *************************************************************************/

    while (!toStop){
        data_container tempData = imitator->update();
        emit sendData(DATA_TYPE_WRITE, tempData.angle, tempData.data);
    }
}
