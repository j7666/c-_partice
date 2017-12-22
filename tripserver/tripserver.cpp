#include "tripserver.h"
#include "clientsocket.h"
#include <iostream>


using namespace std;

tripserver::tripserver(QObject *parent)
    :QTcpServer(parent)
{
    if(!listen(QHostAddress::Any, TRIPPORT ))
        cout << "Tcp Server listen failed.Port = " << TRIPPORT << endl;

}

void tripserver::incomingConnection(int socketDescriptor)
{
    clientsocket *tcpsocket = new clientsocket((QObject*)this);
    tcpsocket->setSocketDescriptor(socketDescriptor );
    cout << "new Tcp connection" << "client ip:" << tcpsocket->peerAddress().toString().toStdString() << "port:" << tcpsocket->peerPort() << endl;
}
