#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

#define HOSTIP "127.0.0.1"
#define TRIPPORT 7990

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    connect(ui->pushButtonSearch,SIGNAL(clicked(bool)),this,SLOT(Search()) );
    connect(ui->pushButtonStop,SIGNAL(clicked(bool)),this,SLOT(StopSearch()) );
    connect(ui->pushButtonQuit,SIGNAL(clicked(bool)),this,SLOT(Quit()) );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::ConnectToServer()
{
    tcpsocket = new QTcpSocket;
    QHostAddress address(HOSTIP);
    tcpsocket->connectToHost(address,TRIPPORT);
}

void Widget::SendRequest()
{

    tcpsocket->write("sendrequest",sizeof("sendrequest"));
    tcpsocket->close();

}

void Widget::Search()
{
    ConnectToServer();
    SendRequest();

}

void Widget::StopSearch()
{

}

void Widget::Quit()
{

}
