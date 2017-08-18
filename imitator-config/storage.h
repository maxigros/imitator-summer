#ifndef STORAGE_H
#define STORAGE_H

#include "imitator_headers.h"


class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);
    ~Storage();
    void process(QString configFilename);
private:
    QFile configFile;
signals:
    void sendInfo(int info);
public slots:

/******************************************************************************
 * Параметры
 *****************************************************************************/
public:
    struct conf{
        QMap<QString, double> simple;
        QList<QMap<QString, double>> targets;
    } parameters;
};

#endif // STORAGE_H
