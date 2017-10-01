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

    // Локатор
     _locator = new Locator();
     _locator->configure(params);
     connect(this, SIGNAL(finish()), _locator, SLOT(deleteLater()));

     // Выбор типа приемника
     _receiver = new ReceiverRadio();
     _receiver->configure(params);
     connect(this, SIGNAL(finish()), _receiver, SLOT(deleteLater()));

     // Параметры для update()
     maxStepsInFrame = (int)params->parameters.simple.value("LOCATOR_ENCODER_RESOLUTION");
     stepSizeWithThinning = params->parameters.simple.value("THINNING");
     thinStepsInFrame = (int)(maxStepsInFrame / stepSizeWithThinning);
     angleDelta = 2 * M_PI / thinStepsInFrame;
     world_time_delta = angleDelta / _locator->speed;

     // В приемнике нужны параметры для Time
     _receiver->setParamsForTime(thinStepsInFrame, world_time_delta);

     // Цели
     targets_num = params->parameters.targets.count();
     qDebug() << QString("%1 targets in config").arg(targets_num);
     for (int i = 0; i < targets_num; i++){
         _targets.append(new TargetConstSpeed());
//         _targets[i] = new TargetConstSpeed();
          // Передаем параметры ТОЛЬКО ОДНОЙ цели
         _targets[i]->configure(params->parameters.targets[i]);
         connect(this, SIGNAL(finish()), _targets[i], SLOT(deleteLater()));
     }
}

data_container DataSource::update()
{
    // Движение целей
    for (int i = 0; i < targets_num; i++)
        _targets[i]->i_update(world_time_delta);

    // Поворот локатора
    _locator->spin(world_time_delta);

    // Подготовка приемника
    _receiver->blank();

    // Контейнер для сгенерированных данных
    data_container temp_data;
    // Текущий угол
    temp_data.angle = currentAngle;
    // Массив отсчетов для текущего угла
    temp_data.data = _receiver->i_receive(currentAngle, _targets, _locator);

    // Меняем текущий угол для следующего кадра
    currentAngle += stepSizeWithThinning;
    // Следующий обзор
    if (currentAngle >= thinStepsInFrame){
        // Обнуляем текущий угол, т.к. новый обзор
        currentAngle = 0;
        // Флаг нового кадра (исп. в дальнейшей обработке)

        !!! исправить frame на overview
        temp_data.frame_flag = 1;
    }

    // Передаем данные для последующей обработки
    return temp_data;
}
