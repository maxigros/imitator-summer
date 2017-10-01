#ifndef TARGETGENERAL_H
#define TARGETGENERAL_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"

class TargetGeneral : public QObject
{
    Q_OBJECT
public:
    explicit TargetGeneral(QObject *parent = 0);
    ~TargetGeneral();
    void configure(QMap<QString, double> currentTarget);
    double getDistance();
    double getPlace();
    double getAzimuth();
    double getSpeed();

    // Интерфейс
    void i_update(double world_time_delta);

protected:
    mt19937 generator;
    void translateCoordsToSphere();

    // Переопределяется в наследниках
    virtual void update(double world_time_delta);

    /**************************************************************************
     * Технические параметры имитатора
     *************************************************************************/
protected:
    //
    QMap<QString, double> place_coordinates;
    QMap<QString, double> speed_coordinates;
    QMap<QString, double> sphere_coordinates;
    double gain;
    double rcs_sigma;
    double mu;
    double speed_sigma;
    double speed_mu;

};

#endif // TARGETGENERAL_H
