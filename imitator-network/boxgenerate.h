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
public slots:
    void getInfo(int info);
private:
    QMap<QString, double> mapConfigParams;
    void run();
signals:
    // Шлем конфигурационные параметры в BoxNetwork
    void sendConfigParams(QMap<QString, double> params);
    // Шлем данные в BoxNetwork
    void sendData(int data_type, double angle, complex<double> *data);
};

#endif // BOXGENERATE_H
