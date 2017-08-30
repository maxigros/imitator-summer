#ifndef IMITATOR_HEADERS_H
#define IMITATOR_HEADERS_H

#define WRITER_MODE_NETWORK     0
#define WRITER_MODE_FILE        1
#define DATA_TYPE_NEW_FRAME     1
#define DATA_TYPE_WRITE         2
#define DATA_TYPE_STOP_WRITING  3
#define INFO_ALL_CONNECTED      1
#define INFO_SERVER_FINISHED    2
#define INFO_CONFIG_ERROR       3
#define SOCKET_ID_DATA          1
#define SOCKET_ID_LOG           2
#define SOCKET_ID_TELEM         3
#define SOCKET_ID_MANAGE        4

#include <QObject>
#include <QMap>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>
#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include <QThread>
#include <iostream>
#include <complex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDateTime>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QtMath>
#include <math.h>
#include <random>
using namespace std;

#endif // IMITATOR_HEADERS_H
