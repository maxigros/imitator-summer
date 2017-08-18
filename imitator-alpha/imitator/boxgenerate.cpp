#include "boxgenerate.h"

BoxGenerate::BoxGenerate(QString configFilename, QObject *parent) : QObject(parent)
{
    filename = configFilename;
    params = new Storage();
    connect(params, SIGNAL(sendInfo(int)), this, SLOT(getInfo(int)));
    connect(this, SIGNAL(finish()), params, SLOT(deleteLater()));
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
    // Создание общего класса DataSource (внутри будут остальные)
    // ----------------------------------
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // -----------------------------------
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
     *************************************************************************/

    /*
     * Один проход WHILE - это один обзор на 360 (new frame)
     * внутри WHILE:
     *      цикл FOR для всех направлений (углов), для каждого:
     *          повернуть локатор
     *          переместить цели
     *          принять все цели на приемник
     *          отправить пакет данных клиенту
     *
     */

    /*
     * while(!toStop)
     * {
     *      QMap<int, complex<double>> DataSource::update();
     * }
     */



    // Заглушка WHILE
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
