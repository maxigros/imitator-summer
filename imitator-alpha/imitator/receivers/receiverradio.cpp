#include "receiverradio.h"

ReceiverRadio::ReceiverRadio()
{
    qDebug() << "ReceiverRadio create";
}

ReceiverRadio::~ReceiverRadio()
{
    qDebug() << "ReceiverRadio deleting";
}

complex<double> *ReceiverRadio::receive(double currentAngle,
                                        QList<TargetGeneral*> targets,
                                        Locator *locator)
{
    // Обрабатываем все цели по очереди
    for (int i = 0; i < targets.count(); i++){
        // Проверяем видимость цели для локатора
        double target_gain = locator->gainForTarget(targets[i]);
        if (target_gain){
            // Задержка до прихода сигнала
            double tau = targets[i]->getDistance() / 3e+8;
            // Индекс приемного массива, с которого в него надо добавлять
            // отсчеты принятого сигнала
            int down = floor((tau + impulseDuration) / periodSampling);
            // Проверяем, что эхо-сигнал успевает прийти до закрытия приемника
            if (down < sizeEchoArray){
                // Ищем верхнюю "границу" импульса (индекс массива,
                // на котором заканчивается импульс)
                int up = ceil((tau + 2*impulseDuration) / periodSampling);
                // Если превышаем размер приемного массива, то используем
                // максимально возможное значение
                if (up > sizeEchoArray)
                    up = sizeEchoArray;
                // Достаем время, соответствующее данному угловому направлению
                double currentTime = _time->getTime(currentAngle, 0) - tau;
                double targetRadialSpeed =
                        targets[i]->getSpeed() *
                        cos(locator->getLocatorAzimuth() - targets[i]->getAzimuth());
                complex<double> t_signal = signalFunctionDopler(currentTime,
                                                                targetRadialSpeed);
                for (int k = down; k < up; k++)
                    echoArray[k] += t_signal;

            }
        }
    }
    return echoArray;
}

complex<double> ReceiverRadio::signalFunction(double t)
{
    return complex<double>(0, 2*M_PI * signalFrequency * t);
}

complex<double> ReceiverRadio::signalFunctionDopler(double t, double speed)
{
    return signalFunction(t) * dopler(t, speed);
}
