#include "boxnetwork.h"

BoxNetwork::BoxNetwork(QString configWriterMode, QObject *parent) : QObject(parent)
{
    cout << "moduleNetwork created with mode: " << configWriterMode.toStdString() << endl;
}

BoxNetwork::~BoxNetwork()
{
    cout << "moduleNetwork deleting" << endl;
    // удалить сокеты
}

void BoxNetwork::stop()
{
    cout << "moduleNetwork stopping" << endl;
    // ToDo: Закрыть сокеты
    toStop = true;
    emit finish();
}

void BoxNetwork::process()
{
    cout << "moduleNetwork processing" << endl;
    int c = 0;
    while(!toStop)
    {
        c++;
    }
}

