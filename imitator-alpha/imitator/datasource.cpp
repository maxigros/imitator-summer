#include "datasource.h"

DataSource::DataSource(QObject *parent) : QObject(parent)
{
    qDebug() << "DataSource created";
}

DataSource::~DataSource()
{
    qDebug() << "DataSource deleting";
    emit finish();
}

void DataSource::configure(Storage *params)
{
    qDebug() << "DataSource configure";

    // Параметры для update()
    maxStepsInFrame = (int)params->parameters.simple.value("LOCATOR_ENCODER_RESOLUTION");
    stepSizeWithThinning = params->parameters.simple.value("THINNING");
    thinStepsInFrame = (int)(maxStepsInFrame / stepSizeWithThinning);


    // Локатор
     _locator = new Locator();
     _locator->configure(params);
     connect(this, SIGNAL(finish()), _locator, SLOT(deleteLater()));

     // Выбор типа приемника
     _receiver = new ReceiverRadio();
     _receiver->configure(params);
     connect(this, SIGNAL(finish()), _receiver, SLOT(deleteLater()));
     // Цели
     targets_num = params->parameters.targets.count();
     qDebug() << QString("%1 targets in config").arg(targets_num);
     for (int i = 0; i < targets_num; i++){
         _targets[i] = new TargetConstSpeed();
         // Передаем параметры ТОЛЬКО ОДНОЙ цели
         _targets[i]->configure(params->parameters.targets[i]);
         connect(this, SIGNAL(finish()), _targets[i], SLOT(deleteLater()));
     }
}

data_container DataSource::update()
{
//    qDebug() << "DataSource update";
//    data_container tempD;
//    tempD.angle = 5;
//    tempD.data = new complex<double>[20];
//    for (int i = 0; i < 20; i++){
//        tempD.data[i] = complex<double>(i, i);
//    }
//    return tempD;


    // Targets move
    for (int i = 0; i < targets_num; i++)
        _targets[i]->i_update();

    // Locator spin

    data_container temp_data;
    temp_data.angle = currentAngle;
//    temp_data.data =

    // For next overview
    currentAngle += stepSizeWithThinning;

    if (currentAngle >= thinStepsInFrame)
        currentAngle = 0;
}
