#ifndef TCPRECEIVE_H
#define TCPRECEIVE_H

#include <iostream>
#include <QTcpServer>
#include <QObject>
#include <pub.h>
#include <QTcpSocket>

using namespace std;
class tcpreceive : public QObject
    {
        Q_OBJECT
    public:
        tcpreceive();
        QTcpServer *m_tcpServer;
        QTcpSocket *m_tcpSocket;
        void start();
    public slots:
        void newTcpSocket();
        void Read();
    };

#endif // TCPRECEIVE_H
