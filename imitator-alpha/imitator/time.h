#ifndef TIME_H
#define TIME_H

#include "imitator_headers.h"

class Time
{
public:
    Time(double periodImpulseRepeat, double periodSampling, double thinStepsInFrame, double timePause);
    double getTime(double currentAngle, double currentMoment);

private:
    double t_currentAngle;
    double t_periodImpulseRepeat;
    double t_periodSampling;
    double t_timeStep;
    int t_n;
    int t_k;
};

#endif // TIME_H
