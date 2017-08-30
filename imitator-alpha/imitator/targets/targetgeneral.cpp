#include "targetgeneral.h"

TargetGeneral::TargetGeneral(QObject *parent) : QObject(parent)
{
    qDebug() << "TargetGeneral create";
}

TargetGeneral::~TargetGeneral()
{
    qDebug() << "TargetGeneral deleting";
}

void TargetGeneral::configure(QMap<QString, double> currentTarget)
{
    // Check config
    if (!(currentTarget.keys().contains("x0") &&
          currentTarget.keys().contains("y0") &&
          currentTarget.keys().contains("z0") &&
          currentTarget.keys().contains("Vx") &&
          currentTarget.keys().contains("Vy") &&
          currentTarget.keys().contains("Vz") &&
          currentTarget.keys().contains("rcs_sigma"))){
        qDebug() << "TargetGeneral configure error";
        return;
    }

    place_coordinates["x"] = currentTarget.value("x0");
    place_coordinates["y"] = currentTarget.value("y0");
    place_coordinates["z"] = currentTarget.value("z0");
    speed_coordinates["Vx"] = currentTarget.value("Vx");
    speed_coordinates["Vy"] = currentTarget.value("Vy");
    speed_coordinates["Vz"] = currentTarget.value("Vz");
    translateCoordsToSphere();

    // Static gain and rcs only !!!
    rcs_sigma = currentTarget.value("rcs_sigma");
    gain = 100;

    // Const speed
    if (currentTarget.keys().contains("speed_sigma")){
        qDebug() << "TargetGeneral configure ConstSpeedTarget";
        speed_mu = currentTarget.value("mu");
        speed_sigma = currentTarget.value("speed_sigma");
    }

    // Const acceleration
    if (currentTarget.keys().contains("acceleration_sigma")){
        qDebug() << "TargetGeneral configure ConstAccelerationTarget";
    }

    // Unknown
    if (!(currentTarget.keys().contains("speed_sigma") &&
          currentTarget.keys().contains("acceleration_sigma"))){
        qDebug() << "TargetGeneral configure error unknown target";
        return;
    }
}

double TargetGeneral::getDistance()
{
    return sphere_coordinates.value("r");
}

double TargetGeneral::getPlace()
{
    return sphere_coordinates.value("pl");
}

double TargetGeneral::getAzimuth()
{
    return sphere_coordinates.value("az");
}

double TargetGeneral::getSpeed()
{
    double t = (place_coordinates.value("x") * speed_coordinates.value("Vx") +
                place_coordinates.value("y") * speed_coordinates.value("Vy") +
                place_coordinates.value("z") * speed_coordinates.value("Vz")) /
            sphere_coordinates.value("r");
    return t;
}

void TargetGeneral::i_update()
{
    update();
}

void TargetGeneral::translateCoordsToSphere()
{
    sphere_coordinates["r"] = sqrt(pow(place_coordinates.value("x"), 2) +
                                   pow(place_coordinates.value("y"), 2) +
                                   pow(place_coordinates.value("z"), 2));
    sphere_coordinates["pl"] = acos(place_coordinates.value("z") /
                                    sphere_coordinates.value("r"));
    sphere_coordinates["az"] = atan2(place_coordinates.value("y"),
                                     place_coordinates.value("x"));
}

void TargetGeneral::update()
{

}
