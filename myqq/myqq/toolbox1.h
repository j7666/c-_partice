#ifndef TOOLBOX1_H
#define TOOLBOX1_H

#include <QToolBox>
#include <QToolButton>
#include "widget.h"
#include <QTcpSocket>
#include <QAbstractSocket>

#define CLIENTCOUNT 256

class toolbox1 : public QToolBox
    {
        Q_OBJECT
    public:
        explicit toolbox1(QWidget *parent = 0);

    signals:

    public slots:

        bool eventFilter(QObject *watched, QEvent *event);

    private:

        int userid;
        QString passwd;
        QString hostip;
        int hostport;

        QString username[CLIENTCOUNT];
        QToolButton *toolBtn[CLIENTCOUNT];
        Widget *child[CLIENTCOUNT];
        void init_toolBtn();
        void init_username();
        QTcpSocket *socketClient;

    private slots:
        void sock_Error(QAbstractSocket::SocketError sockErr );
        void read_Msg();
        void socket_connected();

    };

#endif // TOOLBOX1_H
