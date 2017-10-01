#include "targetconstspeed.h"

TargetConstSpeed::TargetConstSpeed()
{
    qDebug() << "TargetConstSpeed create";
}

TargetConstSpeed::~TargetConstSpeed()
{
    qDebug() << "TargetConstSpeed deleting";
}

void TargetConstSpeed::update(double world_time_delta)
{
    // Генерируется сэмпл с нормальным распределением
    normal_distribution<double> distr(speed_mu, speed_sigma);
    double sample = distr(generator);

    // Вспомогательный контейнер для автоматизации
    QMap<QString, QString> zip;
    zip["x"] = "Vx";
    zip["y"] = "Vy";
    zip["z"] = "Vz";

    // Обновление значений координат(декартовых) и проекций скорости
    foreach (QString key, zip.keys()) {
        place_coordinates[key] =
                place_coordinates.value(key) +
                speed_coordinates.value(zip.value(key)) * world_time_delta +
                sample * pow(world_time_delta ,2);
        speed_coordinates[zip.value(key)] =
                speed_coordinates.value(zip.value(key)) +
                sample * world_time_delta;
    }

    // Обновление сферических координат
    translateCoordsToSphere();
}
