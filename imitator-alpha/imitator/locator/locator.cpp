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
    qDebug() << "Locator spin";
    //self.locator_angle = (self.locator_angle + self.speed * world_time_delta) % 6.28
    locator_angle = 2* M_PI * (locator_angle + speed * world_time_delta);
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
    for (double d = - zero_x; d < zero_x; d += step)
        x_angles.append(d);
    for (double d = - zero_z; d < zero_z; d += step)
        z_angles.append(d);

    // Забиваем массивы расчитываемыми значениями
    for (int i = 0; i < x_angles.count(); i++)
        x_values[i] = sin(mul_x * sin(x_angles[i])) / (mul_x * sin(x_angles[i]));
    for (int i = 0; i < z_angles.count(); i++)
        z_values[i] = sin(mul_z * sin(z_angles[i])) / (mul_z * sin(z_angles[i]));
}
