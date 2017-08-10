#ifndef BOXGENERATE_H
#define BOXGENERATE_H

#include "imitator_headers.h"

class BoxGenerate : public QObject
{
    Q_OBJECT
public:
    explicit BoxGenerate(QString configFilename, QObject *parent = 0);
    ~BoxGenerate();

    /**************************************************************************
     *  Threads
     *************************************************************************/
public:
    void stop();
private:
    bool toStop = false;
signals:
    void finish();  // исп. в mainwindow
public slots:
    void process();

    /**************************************************************************
     *  Управление работой
     *************************************************************************/
public:
private:
    QMap<QString, double> mapConfigParams;
signals:
    // Шлем конфигурационные параметры в BoxNetwork
    void sendConfigParams(QMap<QString, double> params);
    // Шлем данные из BoxNetwork
    void sendData(int data_type, double angle, complex<double> *data);
};

#endif // BOXGENERATE_H
