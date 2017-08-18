#include "boxgenerate.h"

BoxGenerate::BoxGenerate(QString configFilename, QObject *parent) : QObject(parent)
{
    qDebug() << QString("BoxGenerate created with file: %1").arg(configFilename);
    filename = configFilename;
    params = new Storage();
    connect(params, SIGNAL(sendInfo(int)), this, SLOT(getInfo(int)));
    connect(this, SIGNAL(finish()), params, SLOT(deleteLater()));
}

BoxGenerate::~BoxGenerate()
{
    qDebug() << "BoxGenerate deleting";
}

void BoxGenerate::stop()
{
    qDebug() << "BoxGenerate stopping";
    toStop = true;
    emit finish();
}

void BoxGenerate::process()
{
    qDebug() << "BoxGenerate processing";
    params->process(filename);
    // Отправляем в BoxWriter
    emit sendConfigParams(params);
    qDebug() << "BoxGenerate return processing";
}

void BoxGenerate::getInfo(int info)
{
    switch (info) {
    case INFO_ALL_CONNECTED:
        qDebug() << "BoxGenerate getInfo ALL_CONNECTED";
        run();
        break;
    case INFO_CONFIG_ERROR:
        qDebug() << "BoxGenerate getInfo CONFIG_ERROR";
        stop();
        break;
    default:
        break;
    }
}

void BoxGenerate::run()
{
    /**************************************************************************
     * Generation
     *************************************************************************/
    int counter = 0;
    complex<double> *data;
    data = new complex<double>[10];
    for (int i = 0; i < 10; i++)
        data[i] = complex<double>((double)(i), -(double)(i));

    while(!toStop){
        counter++;
        if (counter == 10e8){
            counter = 0;
            emit sendData(DATA_TYPE_WRITE, 10, data);
            qDebug() << "BoxGenerate EMIT";
        }
    }
}
