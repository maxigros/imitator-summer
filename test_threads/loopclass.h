#ifndef LOOPCLASS_H
#define LOOPCLASS_H

#include <QObject>
#include <iostream>
using namespace std;

class LoopClass : public QObject
{
    Q_OBJECT

public:
    LoopClass();
    ~LoopClass();

private:
    int counter;

signals:
    void gogo();

public slots:
    void process();
};

#endif // LOOPCLASS_H
