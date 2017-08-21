#ifndef RECEIVERGENERAL_H
#define RECEIVERGENERAL_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"

class ReceiverGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverGeneral(QObject *parent = 0);
    ~ReceiverGeneral();
    void configure(Storage *params);

    // Интерфейсы

    // Переопределяются в наследниках

    /**************************************************************************
     * Технические параметры имитатора
     *************************************************************************/
protected:
    // Размер массива данных эхо-сигнала
    int sizeEchoArray;
    // Период дискретизации АЦП
    double periodSampling;
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
};

#endif // RECEIVERGENERAL_H
