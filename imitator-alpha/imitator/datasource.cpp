#include "datasource.h"

DataSource::DataSource(QObject *parent) : QObject(parent)
{
    qDebug() << "DataSource created";
}

DataSource::~DataSource()
{
    qDebug() << "DataSource deleting";
}

void DataSource::configure(Storage *params)
{
    qDebug() << "DataSource configure";
}

data_container DataSource::update()
{
//    qDebug() << "DataSource update";
    data_container tempD;;
    tempD.angle = 5;
    tempD.data = new complex<double>[20];
    for (int i = 0; i < 20; i++){
        tempD.data[i] = complex<double>(i, i);
    }
    return tempD;
}
