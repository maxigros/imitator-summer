#ifndef BOXGENERATE_H
#define BOXGENERATE_H

#include <QObject>
#include <iostream>
using namespace std;

class BoxGenerate : public QObject
{
    Q_OBJECT
public:
    explicit BoxGenerate(QString configFilename, QObject *parent = 0);
    ~BoxGenerate();
    void stop();

private:
    bool toStop = false;

signals:
    void finish();  // исп. в mainwindow

public slots:
    void process();
};

#endif // BOXGENERATE_H
