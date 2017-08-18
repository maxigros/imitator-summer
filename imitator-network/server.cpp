#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    cout << "Server created" << endl;

    serverManage = new QTcpServer;
    serverData = new QTcpServer;
    connect(serverManage, SIGNAL(newConnection()), this, SLOT(serverManageNewConnection()));
    connect(serverData, SIGNAL(newConnection()), this, SLOT(serverDataNewConnection()));

    if (!serverManage->listen(QHostAddress::Any, 2011)){
        cout << "Unable to start serverManage: "
             << QString(serverManage->errorString()).toStdString() << endl;
        serverManage->close();
        return;
    }
    if (!serverData->listen(QHostAddress::Any, 2012)){
        cout << "Unable to start serverData: "
             << QString(serverData->errorString()).toStdString() << endl;
        serverData->close();
        return;
    }

    socketManage = new QTcpSocket;
    socketLog = new QTcpSocket;
    socketTelem = new QTcpSocket;
    socketData = new QTcpSocket;
}

Server::~Server()
{
    cout << "Server deleting" << endl;
    serverManage->close();
    serverData->close();

}

void Server::sendToCli(QByteArray *data, int sockID)
{
    switch (sockID) {
    case SOCKET_ID_DATA:
        if (socketData->state() == QAbstractSocket::ConnectedState){
            cout << "Server DATA write" << endl;
            socketData->write(data->data(), data->size());
        }
        break;
    case SOCKET_ID_LOG:
        if (socketLog->state() == QAbstractSocket::ConnectedState){
            cout << "Server LOG write" << endl;
            socketLog->write(data->data(), data->size());
            socketLog->flush();
        }
        break;
    case SOCKET_ID_TELEM:
        if (socketTelem->state() == QAbstractSocket::ConnectedState){
            socketTelem->write(data->data(), data->size());
        }
        break;
    case SOCKET_ID_MANAGE:
        if (socketManage->state() == QAbstractSocket::ConnectedState){
            socketManage->write(data->data(), data->size());
        }
        break;
    default:
        break;
    }

}

void Server::serverManageNewConnection()
{
    cout << "Server socketManage connected" << endl;
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
        cout << "Server socketLog connected" << endl;
        socketLog = serverData->nextPendingConnection();
//        connect(socketLog, SIGNAL(disconnected()),
//                this, SLOT(disconnectAll()));
        break;
    case 3:
        cout << "Server socketTelem connected" << endl;
        socketTelem = serverData->nextPendingConnection();
//        connect(socketTelem, SIGNAL(disconnected()),
//                this, SLOT(disconnectAll()));
        break;
    case 4:
        cout << "Server socketData connected" << endl;
        socketData = serverData->nextPendingConnection();
//        connect(socketData, SIGNAL(disconnected()),
//                this, SLOT(disconnectAll()));
        emit sendInfo(INFO_ALL_CONNECTED);
        break;
    default:
        break;
    }
}

void Server::disconnectAll()
{
    // Поключен только один сокет !!!
    cout << "Server disconnected" << endl;
    socketManage->close();
    socketLog->close();
    socketTelem->close();
    socketData->close();
    emit sendInfo(INFO_SERVER_FINISHED);
}
