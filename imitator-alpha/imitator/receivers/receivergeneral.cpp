#include "receivergeneral.h"

ReceiverGeneral::ReceiverGeneral(QObject *parent) : QObject(parent)
{

}

ReceiverGeneral::~ReceiverGeneral()
{

}

void ReceiverGeneral::configure(Storage *params)
{
    params_temp = params;
    // Check config
    if (!(params_temp->parameters.simple.keys().contains("PULSE_REPEAT_TIME") &&
          params_temp->parameters.simple.keys().contains("FREQUENCY")         &&
          params_temp->parameters.simple.keys().contains("RECEIVER_NOISE") &&
          params_temp->parameters.simple.keys().contains("RECEIVER_TRACT") &&
          params_temp->parameters.simple.keys().contains("ANTENNA_TRACT") &&
          params_temp->parameters.simple.keys().contains("PULSE_DURATION") &&
          params_temp->parameters.simple.keys().contains("LAMBDA") &&
          params_temp->parameters.simple.keys().contains("STATION_POWER") &&
          params_temp->parameters.simple.keys().contains("RECEIVER_GAIN") ))
    {
        // error
        qDebug() << "ReceiverGeneral configure error";
        return;
    }

    periodImpulseRepeat = params_temp->parameters.simple.value("PULSE_REPEAT_TIME");
    signalFrequency = 0;
    periodSampling = 1.0 / params_temp->parameters.simple.value("FREQUENCY");
    sizeEchoArray = (int)(periodImpulseRepeat / periodSampling);
    sigma = sqrt(1.38e-23 * M_PI * 300*
                 (1 + (params_temp->parameters.simple.value("RECEIVER_NOISE") - 1)*
                  params_temp->parameters.simple.value("RECEIVER_TRACT")*
                  params_temp->parameters.simple.value("ANTENNA_TRACT")));

//    // Инициализация массива отсчетов и заполнение его нулями
//    echoArray = new complex<double>[sizeEchoArray];
//    for (int i = 0; i < sizeEchoArray; i++)
//        echoArray[i] = complex<double>(0.0, 0.0);

    impulseDuration = params_temp->parameters.simple.value("PULSE_DURATION");
    waveLength = params_temp->parameters.simple.value("LAMBDA");
    stationPower = params_temp->parameters.simple.value("STATION_POWER");
    receiverGain = params_temp->parameters.simple.value("RECEIVER_GAIN");

    _time = new Time(periodImpulseRepeat,
                     periodSampling,
                     thinStepsInFrame,
                     world_time_delta);
}

void ReceiverGeneral::blank()
{
    // Инициализация массива отсчетов
    echoArray = new complex<double>[sizeEchoArray];

    // Заполнение массива отсчетами шума антенно-приемного тракта
    normal_distribution<double> distr(mu, sigma);
    for (int i = 0; i < sizeEchoArray; i++){
        echoArray[i] = complex<double>(distr(generator), distr(generator));
        echoArray[i] *= receiverGain;
    }
}

void ReceiverGeneral::setParamsForTime(double t_thinStepsInFrame, double t_world_time_delta)
{
    thinStepsInFrame = t_thinStepsInFrame;
    world_time_delta = t_world_time_delta;
}

complex<double> *ReceiverGeneral::i_receive(double currentAngle, QList<TargetGeneral*> targets, Locator* locator)
{
    return receive(currentAngle, targets, locator);
}

complex<double> ReceiverGeneral::dopler(double t, double speed)
{
    double dopler_freq = 2 * speed / waveLength;
    return complex<double>(-2*M_PI* dopler_freq * t);
}

complex<double> *ReceiverGeneral::receive(double currentAngle, QList<TargetGeneral *> targets, Locator *locator)
{
    Q_UNUSED(currentAngle);
    Q_UNUSED(targets);
    Q_UNUSED(locator);
    return NULL;
}
