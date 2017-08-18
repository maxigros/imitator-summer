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
    bool waiting_for_info = true;
    int data_array_len;     // Характеристика приемника,
                            // знаем из конфигурации имитатора
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
};

#endif // BOXNETWORK_H
