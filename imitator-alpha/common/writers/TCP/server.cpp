#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    serverManage = new QTcpServer;
    serverData = new QTcpServer;
    connect(serverManage, SIGNAL(newConnection()), this, SLOT(serverManageNewConnection()));
    connect(serverData, SIGNAL(newConnection()), this, SLOT(serverDataNewConnection()));

    socketManage = new QTcpSocket;
    socketLog = new QTcpSocket;
    socketTelem = new QTcpSocket;
    socketData = new QTcpSocket;
}

Server::~Server()
{
    serverManage->close();
    serverData->close();
}

void Server::start()
{
    if (!serverManage->listen(QHostAddress::Any, 2011)){
        qDebug() << QString("Server::start error: unable to start serverManage: %1")
                    .arg(serverManage->errorString());
        serverManage->close();
        return;
    }
    if (!serverData->listen(QHostAddress::Any, 2012)){
        qDebug() << QString("Server::start error: unable to start serverData: %1")
                    .arg(serverData->errorString());
        serverData->close();
        return;
    }
}

void Server::sendToCli(QByteArray *data, int sockID)
{
    switch (sockID) {
    case SOCKET_ID_DATA:
        if (socketData->state() == QAbstractSocket::ConnectedState){
            qDebug() << "Socket DATA write";
            socketData->write(data->data(), data->size());
            socketData->flush();
        }
        break;
    case SOCKET_ID_LOG:
        if (socketLog->state() == QAbstractSocket::ConnectedState){
            qDebug() << "Socket LOG write";
            socketLog->write(data->data(), data->size());
            socketLog->flush();
        }
        break;
    case SOCKET_ID_TELEM:
        if (socketTelem->state() == QAbstractSocket::ConnectedState){
            qDebug() << "Socket TELEM write";
            socketTelem->write(data->data(), data->size());
        }
        break;
    case SOCKET_ID_MANAGE:
        if (socketManage->state() == QAbstractSocket::ConnectedState){
            qDebug() << "Socket MANAGE write";
            socketManage->write(data->data(), data->size());
        }
        break;
    default:
        break;
    }

}

void Server::serverManageNewConnection()
{
    qDebug() << "Server::newConnection: socketManage connected";
    socketManage = serverManage->nextPendingConnection();
    connect(socketManage, SIGNAL(disconnected()),
            this, SLOT(disconnectAll()));
    statusByte++;
}

void Server::serverDataNewConnection()
{
    statusByte++;
    switch (statusByte) {
    case 2:
        qDebug() << "Server::newConnection: socketLog connected";
        socketLog = serverData->nextPendingConnection();
        break;
    case 3:
        qDebug() << "Server::newConnection: socketTelem connected";
        socketTelem = serverData->nextPendingConnection();
        break;
    case 4:
        qDebug() << "Server::newConnection: socketData connected";
        socketData = serverData->nextPendingConnection();
        emit sendInfo(INFO_ALL_CONNECTED);
        break;
    default:
        break;
    }
}

void Server::disconnectAll()
{
    // Поключен только один сокет !!!
    qDebug() << "Server disconnected";
    socketManage->close();
    socketLog->close();
    socketTelem->close();
    socketData->close();
    emit sendInfo(INFO_SERVER_FINISHED);
}
