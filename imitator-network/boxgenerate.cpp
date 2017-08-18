#include "boxgenerate.h"

BoxGenerate::BoxGenerate(QString configFilename, QObject *parent) : QObject(parent)
{
    cout << "BoxGenerate created with file: " << configFilename.toStdString() << endl;
}

BoxGenerate::~BoxGenerate()
{
    cout << "BoxGenerate deleting" << endl;
}

void BoxGenerate::stop()
{
    cout << "BoxGenerate stopping" << endl;
    toStop = true;
    emit finish();
}

void BoxGenerate::process()
{
    cout << "BoxGenerate processing" << endl;

    // QMap заполняется из файла конфигурации
    mapConfigParams["PARAM_DATA_ARRAY_LEN"] = 20;
    emit sendConfigParams(mapConfigParams);
}

void BoxGenerate::getInfo(int info)
{
    if (info == INFO_ALL_CONNECTED)
        run();
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
            cout << "BoxGenerate EMIT" << endl;
        }
    }
}
