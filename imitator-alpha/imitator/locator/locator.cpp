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
}

void Locator::spin()
{
    qDebug() << "Locator spin";
}
