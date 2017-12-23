#include "clientsocket.h"
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>


clientsocket::clientsocket(QObject *parent): QTcpSocket(parent)
{
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()) );
    connect(this,SIGNAL(readyRead()),this, SLOT(readData()) );
}

void clientsocket::readData()
{
    QDataStream in(this);
//    char buff[50];
//    memset(buff,0,sizeof(buff));
//    read(buff, 5);
//    printf("buff = %s\n",buff);

    quint16 num;
    quint8 s;
    QString from,to;
    QDate date;
    QTime time;
    in >> num;
    in >> s;
    in >> from;
    in >> to;
    in >> date;
    in >> time;

printf("num = %d\n",num);

printf("s=%c\n",s);

printf("from=%s\n",from.toStdString().data() );

printf("to=%s\n",to.toStdString().data());

printf("date=%s, time=%s\n",date.toString().toStdString().data(),time.toString().toStdString().data() );

}
