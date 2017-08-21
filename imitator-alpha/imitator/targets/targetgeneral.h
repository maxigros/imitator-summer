#ifndef TARGETGENERAL_H
#define TARGETGENERAL_H

#include "../imitator_headers.h"
#include "../../common/config_storage/storage.h"

class TargetGeneral : public QObject
{
    Q_OBJECT
public:
    explicit TargetGeneral(QObject *parent = 0);
    ~TargetGeneral();
    void configure(QMap<QString, double> currentTarget);

signals:

public slots:
};

#endif // TARGETGENERAL_H
