#ifndef TRIPSERVER_H
#define TRIPSERVER_H
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

#define TRIPPORT 7990

class tripserver : public QTcpServer
    {
        Q_OBJECT
    public:
        tripserver(QObject *parent =0);
        void incomingConnection(int socketDescriptor);
    };

#endif // TRIPSERVER_H
