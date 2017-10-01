#include "locator.h"

Locator::Locator(QObject *parent) : QObject(parent)
{
    qDebug() << "Locator create";
}

Locator::~Locator()
{
    qDebug() << "Locator deleting";
}

void Locator::configure(Storage *params)
{
    qDebug() << "Locator configure";
    params_temp = params;
    // Check config
    if (!(params_temp->parameters.simple.keys().contains("ROTATION_SPEED") &&
          params_temp->parameters.simple.keys().contains("DNA_KPD") &&
          params_temp->parameters.simple.keys().contains("DNA_KIP") &&
          params_temp->parameters.simple.keys().contains("X_SIZE") &&
          params_temp->parameters.simple.keys().contains("Z_SIZE") &&
          params_temp->parameters.simple.keys().contains("LAMBDA") ))
    {
        // error
        qDebug() << "Locator configure error";
        return;
    }

    speed = qDegreesToRadians(params_temp->parameters.simple.value("ROTATION_SPEED"));
    locator_angle = 0.0;
    locator_place = qDegreesToRadians(90.0);
    locator_gain = params_temp->parameters.simple.value("DNA_KPD") *
                   params_temp->parameters.simple.value("DNA_KIP") *
                   params_temp->parameters.simple.value("X_SIZE") *
                   params_temp->parameters.simple.value("Z_SIZE") *
                   4 * M_PI /
                   qPow(params_temp->parameters.simple.value("LAMBDA"), 2);

    // Тип ДНА
    simpleDNA();
}

void Locator::spin(double world_time_delta)
{
    // Обновление текущего угла поворота локатора
    locator_angle = (locator_angle + speed * world_time_delta) % (2*M_PI);
}

double Locator::gainForTarget(TargetGeneral *target)
{
    // Радиоимпульс
    return gainForTargetAzimuth(target);
}

double Locator::gainForTargetAzimuth(TargetGeneral *target)
{
    // Пределы диаграммы
    double zero_x = params_temp->parameters.simple.value("X_START");

    double target_azimuth = target->getAzimuth() - locator_angle;
        if ((target_azimuth > -zero_x) && (target_azimuth < zero_x))
            for (int i = 1; i < x_angles.count(); i++)
                if (x_angles[i] >= target_azimuth)
                    return interpolate(target_azimuth,
                                       x_angles[i - 1], // x1
                                       x_angles[i],     // x2
                                       x_values[i - 1], // y1
                                       x_values[i]);    // y2
        return 0;
}

double Locator::getLocatorAzimuth()
{
    return locator_angle;
}

void Locator::simpleDNA()
{
    qDebug() << "Locator simpleDNA";
    // Check config
    if (!(params_temp->parameters.simple.keys().contains("SIMPLE_STEP") &&
          params_temp->parameters.simple.keys().contains("X_START") &&
          params_temp->parameters.simple.keys().contains("Z_START") &&
          params_temp->parameters.simple.keys().contains("LAMBDA") ))
    {
        // error
        qDebug() << "Locator simpleDNA configure error";
        return;
    }

    // Волновое число
    double wave_number = M_PI / params_temp->parameters.simple.value("LAMBDA");

    // Пределы диаграммы
    double zero_x = params_temp->parameters.simple.value("X_START");
    double zero_z = params_temp->parameters.simple.value("Z_START");

    // Множители из формулы sin(x)/x
    double mul_x = wave_number * params_temp->parameters.simple.value("X_SIZE");
    double mul_z = wave_number * params_temp->parameters.simple.value("Z_SIZE");

    // Углы
    double step = params_temp->parameters.simple.value("SIMPLE_STEP");
    for (double d = - zero_x; d < zero_x; d += step){
        x_angles.append(d);
        x_values.append(0);
    }
    for (double d = - zero_z; d < zero_z; d += step){
        z_angles.append(d);
        z_values.append(0);
    }

    // Забиваем массивы расчитываемыми значениями
    for (int i = 0; i < x_angles.count(); i++)
        x_values[i] = sin(mul_x * sin(x_angles[i])) / (mul_x * sin(x_angles[i]));
    for (int i = 0; i < z_angles.count(); i++)
        z_values[i] = sin(mul_z * sin(z_angles[i])) / (mul_z * sin(z_angles[i]));
}

double Locator::interpolate(double point, double x1, double x2, double y1, double y2)
{
    // Линейная интерполяция, метод Лагранжа
    double L = 0;
    double x[2] = {x1, x2};
    double y[2] = {y1, y2};

    for (int i = 0; i < 2; ++i){
            double l = 1;
            for (int j = 0; j < 2; ++j)
                if (i != j)
                    l *= (point - x[j]) / (x[i] - x[j]);
            L += y[i] * l;
        }
    return L;
}
