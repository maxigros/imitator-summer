#ifndef RECEIVERRADIO_H
#define RECEIVERRADIO_H

#include "receivergeneral.h"

class ReceiverRadio : public ReceiverGeneral
{
    Q_OBJECT
public:
    ReceiverRadio();
    ~ReceiverRadio();

private:
    // Переопределение метода из родительского класса
    complex<double>* receive(double currentAngle, QList<TargetGeneral*> targets, Locator* locator);

    // Модели сигнала
    complex<double> signalFunction(double t);
    complex<double> signalFunctionDopler(double t, double speed);
};

#endif // RECEIVERRADIO_H
