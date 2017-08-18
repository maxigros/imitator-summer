#ifndef SERVER_H
#define SERVER_H

#include "imitator_headers.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void start();
    void sendToCli(QByteArray *data, int sockID = SOCKET_ID_DATA);

private:
    QTcpServer *serverManage;
    QTcpServer *serverData;
    QTcpSocket *socketManage;
    QTcpSocket *socketLog;
    QTcpSocket *socketTelem;
    QTcpSocket *socketData;
    char statusByte = 0;

signals:
    void sendInfo(int info);

private slots:
    void serverManageNewConnection();
    void serverDataNewConnection();
    void disconnectAll();
};

#endif // SERVER_H
