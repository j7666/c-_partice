#include "clientsocket.h"
#include <QDataStream>
#include <QMessageBox>

clientsocket::clientsocket(QObject *parent): QTcpSocket(parent)
{
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()) );
    connect(this,SIGNAL(readyRead()),this, SLOT(readData()) );
}

void clientsocket::readData()
{
    QDataStream in(this);
    char buff[50];
    memset(buff,0,sizeof(buff));
    read(buff, 5);
    printf("buff = %s\n",buff);
}
