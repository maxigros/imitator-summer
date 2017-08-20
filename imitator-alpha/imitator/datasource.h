#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "imitator_headers.h"
#include "../common/config_storage/storage.h"

typedef struct{
    double angle;
    complex<double> *data;
} data_container;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);
    ~DataSource();

    void configure(Storage *params);
    data_container update();

signals:

public slots:
};

#endif // DATASOURCE_H
