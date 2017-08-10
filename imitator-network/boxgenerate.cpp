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
