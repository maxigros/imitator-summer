#ifndef LOCATOR_H
#define LOCATOR_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"

class Locator : public QObject
{
    Q_OBJECT
public:
    explicit Locator(QObject *parent = 0);
    ~Locator();
    void configure(Storage *params);
    void spin(double world_time_delta);

private:
    Storage *params_temp;
    // ДНА вида sin(x)/x
    void simpleDNA();
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
