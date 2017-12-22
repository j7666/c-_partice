#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>

class clientsocket : public QTcpSocket
    {
        Q_OBJECT
    public:
        clientsocket(QObject *parent = 0);

    public slots:
        void readData();

    };

#endif // CLIENTSOCKET_H
