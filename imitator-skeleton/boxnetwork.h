#ifndef BOXNETWORK_H
#define BOXNETWORK_H

#define WRITER_MODE_NETWORK     0
#define WRITER_MODE_FILE        1

#include <QObject>
#include <iostream>
using namespace std;

class BoxNetwork : public QObject
{
    Q_OBJECT
public:
    explicit BoxNetwork(QString configWriterMode, QObject *parent = 0);
    ~BoxNetwork();
    void stop();

private:
    bool toStop = false;

signals:
    void finish();    // исп. в mainwindow
public slots:
    void process();

};

#endif // BOXNETWORK_H
