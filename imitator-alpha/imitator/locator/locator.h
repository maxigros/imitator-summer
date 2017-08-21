#ifndef LOCATOR_H
#define LOCATOR_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"

class Locator : public QObject
{
    Q_OBJECT
public:
    explicit Locator(QObject *parent = 0);
    ~Locator();
    void configure(Storage *params);

signals:

public slots:
};

#endif // LOCATOR_H
