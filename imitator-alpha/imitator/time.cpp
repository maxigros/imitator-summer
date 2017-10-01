#include "time.h"

Time::Time(double periodImpulseRepeat, double periodSampling, double thinStepsInFrame, double timePause)
{
    /*
    periodImpulseRepeat: период повторения импульсов
    periodSampling: период дескритизации АЦП
    thinStepsInFrame: количество различаемых угловых направлений (с учетом прореживания)
    timePause: время стояния в одном угловом направлении
    */
    t_n = (int)(periodImpulseRepeat / periodSampling);
    t_k = thinStepsInFrame;
    t_timeStep = timePause;
    t_periodSampling = periodSampling;
}

double Time::getTime(double currentAngle, double currentMoment)
{
    if (t_k <= currentAngle || t_n <= currentMoment){
        qDebug() << "Time getTime error";
        return 0;
    }
    return currentAngle * t_timeStep + currentMoment * t_periodSampling;
}
