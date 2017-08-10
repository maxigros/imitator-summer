#ifndef BOXNETWORK_H
#define BOXNETWORK_H

#include "imitator_headers.h"
#include "writers_all.h"

class BoxNetwork : public QObject
{
    Q_OBJECT
public:
    explicit BoxNetwork(QString writer_mode, QObject *parent = 0);
    ~BoxNetwork();
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

public slots:
    // Прием конфигурационных параметров из BoxGenerate
    void getConfigParams(QMap<QString, double> params);
    // Прием данных из BoxGenerate
    void getData(int data_type, double angle, complex<double> *data);
};

#endif // BOXNETWORK_H
