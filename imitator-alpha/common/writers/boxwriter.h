#ifndef BOXNETWORK_H
#define BOXNETWORK_H

#include "../../imitator/imitator_headers.h"
#include "../config_storage/storage.h"
#include "TCP/writertcp.h"

class BoxWriter : public QObject
{
    Q_OBJECT
public:
    explicit BoxWriter(QString writer_mode, QObject *parent = 0);
    ~BoxWriter();
    /**************************************************************************
     *  Threads
     *************************************************************************/
public:
    void stop_box();
private:
    bool toStop = false;
signals:
    void finish();    // исп. в mainwindow
public slots:
    void process();

    /**************************************************************************
     *  Управление работой
     *************************************************************************/
private:
    WriterGeneral *writer;
    bool waitingForConfigInfo = true;
    int configWriterMode;
signals:
    void sendInfo(int info);
public slots:
    // Прием конфигурационных параметров из BoxGenerate
    void getConfigParams(Storage* configParams);
    // Прием данных из BoxGenerate
    void getData(int data_type, double angle, complex<double> *data);
private slots:
    void getInfo(int info);

    /**************************************************************************
     * Технические параметры имитатора
     *************************************************************************/
private:
    // Длина массива данных в одном кадре
    int dataArrayLength;

    // Количество угловых направлений по азимуту, поддерживаемых энкодером локатора,
    // т.е. максимально возможное количество "шагов" угла в одном обзоре.
    // Далее упом. как "дискретные шаги"
    int maxStepsInFrame;

    // Размер "прореженного шага" (количество "дискретных шагов" в одном "прореженном")
    double stepSizeWithThinning;

    // Количество "прореженных шагов" в одном обзоре
    int thinStepsInFrame;
};

#endif // BOXNETWORK_H
