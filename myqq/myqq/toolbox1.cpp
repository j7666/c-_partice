#include <QVBoxLayout>
#include "toolbox1.h"
#include <QIcon>
#include <QGroupBox>

#include <QBoxLayout>
#include <QEvent>
#include "logindlg.h"
#include <QMessageBox>
#include <QHostAddress>

toolbox1::toolbox1(QWidget *parent) :
    QToolBox(parent)
    {
        init_username();
        init_toolBtn();
        setWindowIcon(QIcon(":/images/3.png"));

        loginDlg login;
        login.exec();

        if(login.isLogin)
            {
                if(login.userid <0 || login.userid >255)
                    QMessageBox::information(this,"","ERROR");
                else
                    {
                        setWindowTitle(username[login.userid]);
                        userid = login.userid;
                        passwd = login.passwd;
                        hostip = login.hostip;
                        hostport = login.hostport;

                        socketClient = new QTcpSocket(this);
                        connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(sock_Error(QAbstractSocket::SocketAccessError)) );
                        connect(socketClient,SIGNAL(readyRead()),this,SLOT(read_Msg()) );
                        connect(socketClient,SIGNAL(connected()),this,SLOT(socket_connected()));

                        QHostAddress hostAddr(hostip);
                        socketClient->connectToHost(hostAddr,hostport );

                    }
            }
        else
            {
                exit(0);
            }

    }

bool toolbox1::eventFilter(QObject *watched, QEvent *event)
    {
        if(event->type() == QEvent::MouseButtonPress)
            {
                int i = watched->objectName().toInt();
                child[i]->showNormal();
            }
        return QToolBox::eventFilter(watched,event);

    }

void toolbox1::init_toolBtn()
    {
        QString imageName;
        for(int i = 0; i < CLIENTCOUNT; i++)
            {
                toolBtn[i] = new QToolButton();
                toolBtn[i]->setObjectName(QString::number(i));
                toolBtn[i]->installEventFilter(this);
                toolBtn[i]->setText( username[i]);
                imageName.sprintf(":/images/%d.png",i);
                toolBtn[i]->setIcon(QIcon(imageName));
                toolBtn[i]->setIconSize(QPixmap(imageName).size());
                toolBtn[i]->setAutoRaise(true);
                toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
                toolBtn[i]->setToolTip("No User.");
                child[i] = new Widget(this->toolBtn[i]->icon(),i,this->toolBtn[i]->text(),this);

            }


        QGroupBox *groupBox[8];
        QVBoxLayout *layout[8];

        static int index=0;
        for(int i = 0; i< 8; i++)
            {
                groupBox[i] = new QGroupBox;
                layout[i] = new QVBoxLayout(groupBox[i]);
                layout[i]->setMargin(10);
                layout[i]->setAlignment(Qt::AlignHCenter);
                for(int j =0; j<32;j++)
                    {
                        layout[i]->addWidget(toolBtn[index++] );
                    }
            }

        addItem((QWidget *)groupBox[0],tr("1"));
        addItem((QWidget *)groupBox[1],tr("2"));

        addItem((QWidget *)groupBox[2],tr("3"));
        addItem((QWidget *)groupBox[3],tr("4"));

        addItem((QWidget *)groupBox[4],tr("5"));
        addItem((QWidget *)groupBox[5],tr("6"));

        addItem((QWidget *)groupBox[6],tr("7"));
        addItem((QWidget *)groupBox[7],tr("8"));


    }

void toolbox1::init_username()
    {
        for(int i= 0; i < CLIENTCOUNT; i++)
            username[i] = tr("user") + QString::number(i);

    }

void toolbox1::sock_Error(QAbstractSocket::SocketError sockErr)
    {
        switch (sockErr) {
            case QAbstractSocket::RemoteHostClosedError:

                break;
            default:
                QMessageBox::information(this,"Error",socketClient->errorString());
            }
    }

void toolbox1::read_Msg()
    {

    }

void toolbox1::socket_connected()
    {

    }
