#ifndef RECEIVERGENERAL_H
#define RECEIVERGENERAL_H

#include "../imitator_headers.h"

class ReceiverGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverGeneral(QObject *parent = 0);

signals:

public slots:
};

#endif // RECEIVERGENERAL_H
