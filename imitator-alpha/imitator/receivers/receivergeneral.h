#ifndef RECEIVERGENERAL_H
#define RECEIVERGENERAL_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"
#include "../targets/targets.h"
#include "../locator/locator.h"
#include "../time.h"

class ReceiverGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverGeneral(QObject *parent = 0);
    ~ReceiverGeneral();
    void configure(Storage *params);
    void blank();
    void setParamsForTime(double t_thinStepsInFrame, double t_world_time_delta);

    // Интерфейсы
    complex<double>* i_receive(double currentAngle,
                               QList<TargetGeneral*> targets,
                               Locator* locator);

protected:
    Storage *params_temp;
    complex<double> *echoArray;
    mt19937 generator;
    Time *_time;

    complex<double> dopler(double t, double speed);


    // Переопределяются в наследниках
    virtual complex<double>* receive(double currentAngle,
                                     QList<TargetGeneral*> targets,
                                     Locator* locator);
    /**************************************************************************
     * Технические параметры имитатора
     *************************************************************************/
protected:
    // Размер массива данных эхо-сигнала
    int sizeEchoArray;
    // Период дискретизации АЦП
    double periodSampling;
    // Частота сигнала
    double signalFrequency;
    // Период повторения импульсов
    double periodImpulseRepeat;
    // Длительность импульса
    double impulseDuration;
    // Длина волны РЛС
    double waveLength;
    // Мощность излучения
    double stationPower;
    // Коэффициент усиления приемника
    double receiverGain;
    // Количество "прореженных шагов в обзоре"
    double thinStepsInFrame;
    // Период моделирования мира
    double world_time_delta;

    double sigma;
    double mu = 0;
};

#endif // RECEIVERGENERAL_H
