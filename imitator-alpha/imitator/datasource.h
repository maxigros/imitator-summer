#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "imitator_headers.h"
#include "../common/config_storage/storage.h"
#include "receivers/receivers.h"
#include "locator/locator.h"
#include "targets/targets.h"

typedef struct{
    char frame_flag = 0;
    double angle;
    complex<double> *data;
} data_container;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);
    ~DataSource();

    void configure(Storage *params);
    data_container update();
signals:
    void finish();
private:
    Locator *_locator;
    ReceiverGeneral *_receiver;
    QList<TargetGeneral*> _targets;
    double currentAngle = 0;
    int angleCounter = 0;
    int targets_num = 0;

    /**************************************************************************
     * Технические параметры имитатора
     *************************************************************************/

    // Длина массива данных в одном кадре
    int dataArrayLength;

    // Количество угловых направлений по азимуту, поддерживаемых энкодером локатора,
    // т.е. максимально возможное количество "шагов" угла в одном обзоре.
    // Далее упом. как "дискретные шаги"
    int maxStepsInFrame;

    // Размер "прореженного шага" (количество "дискретных шагов" в одном "прореженном")
    double stepSizeWithThinning;

    // Угловой размер одного шага (итогового)
    double angleDelta;

    // Количество "прореженных шагов" в одном обзоре
    int thinStepsInFrame;

    // Период моделирования мира
    double world_time_delta;
};

#endif // DATASOURCE_H
