#ifndef LOCATOR_H
#define LOCATOR_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"
#include "../targets/targets.h"

class Locator : public QObject
{
    Q_OBJECT
public:
    explicit Locator(QObject *parent = 0);
    ~Locator();
    void configure(Storage *params);
    void spin(double world_time_delta);
    double gainForTarget(TargetGeneral *target);
    double gainForTargetAzimuth(TargetGeneral *target);
    double getLocatorAzimuth();

private:
    Storage *params_temp;
    // ДНА вида sin(x)/x
    void simpleDNA();
    // Интерполяция
    double interpolate(double point, double x1, double x2, double y1, double y2);
    /**************************************************************************
     * Технические параметры локатора
     *************************************************************************/
public:
    // Скорость вращения (радиан/с)
    double speed;
private:
    // Текущий угол азимута
    double locator_angle;
    // Текущий угол места
    double locator_place;
    // КУ антенны
    double locator_gain;
    // Время полного оборота
    double full_time_rotate;
    // Для таблицы ДН
    QList<double> x_angles;
    QList<double> z_angles;
    QList<double> x_values;
    QList<double> z_values;
};

#endif // LOCATOR_H
