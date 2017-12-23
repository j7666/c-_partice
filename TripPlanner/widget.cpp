#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QDateTime>
#include <QDebug>

#define HOSTIP "222.111.112.200"
#define TRIPPORT 7990

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    init();



    connect(ui->pushButtonSearch,SIGNAL(clicked(bool)),this,SLOT(Search()) );
    connect(ui->pushButtonStop,SIGNAL(clicked(bool)),this,SLOT(StopSearch()) );
    connect(ui->pushButtonQuit,SIGNAL(clicked(bool)),this,SLOT(Quit()) );
    connect(&tcpsocket,SIGNAL(readyRead()),this,SLOT(readData()) );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::ConnectToServer()
{
    QHostAddress address(HOSTIP);
    tcpsocket.connectToHost(address,TRIPPORT);
    QString message = QString("Connect to Host:%1,Port:%2.Sending Request").arg(HOSTIP).arg(QString::number(TRIPPORT));
    ui->labelMessage->setText(message);
}

void Widget::SendRequest()
{
    printf("send request\n");
    QByteArray data;
    QDataStream out( &data,QIODevice::WriteOnly);  //如何通过stream写数据到socket
//    messagestuct msg;
//    msg.num = 88;
//    msg.s = 's';
//    msg.From = ui->comboBoxFrom->currentText();
//    msg.To = ui->comboBoxTo->currentText();
//    msg.Date = ui->dateEditDate->date().toString();
//    msg.time = ui->timeEditTime->time().toString();  //需要把结构体转换为char*,要考虑字节顺序及字节对齐问题。

//    tcpsocket.write((char *)(&msg),sizeof(msg));

    out << quint16(88);
    out << quint8('s');
    out << ui->comboBoxFrom->currentText();
    out << ui->comboBoxTo->currentText();
    out << ui->dateEditDate->date();
    out << ui->timeEditTime->time();

    tcpsocket.write(data);

    tcpsocket.close();

}

void Widget::init()
{
    QStringList FromList;
    FromList << "上海" << "深圳";
    ui->comboBoxFrom->addItems(FromList);

    QStringList ToList;
    ToList << "北京" << "太原";
    ui->comboBoxTo->addItems(ToList);

    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setColumnCount(6);

    QStringList headerList;
    headerList << "num" << "S" << "from" << "to" << "Date" << "time";
    ui->tableWidget->setHorizontalHeaderLabels(headerList);

    ui->tableWidget->insertRow(0);
//    QTableWidgetItem *item = new QTableWidgetItem("A");
//    ui->tableWidget->setItem(0,0,item);

    QDateTime tm = QDateTime::currentDateTime();
    ui->dateEditDate->setDate(tm.date());
    ui->timeEditTime->setTime(tm.time());

    ui->radioButtonArrival->setChecked(true);

    ui->labelMessage->setText("等待查询");

}

void Widget::Search()
{
    ConnectToServer();
    SendRequest();

}

void Widget::StopSearch()
{
    tcpsocket.disconnectFromHost();
    QString message("disconnectFromHost");
    ui->labelMessage->setText(message);
}

void Widget::Quit()
{
    close();
}

void Widget::readData()
{
    qDebug()<< "read\n";
    QDataStream in(&tcpsocket);

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
  //headerList << "num" << "S" << "from" << "to" << "Date" << "time";
    QTableWidgetItem *item = new QTableWidgetItem(QString(num));
    ui->tableWidget->setItem(0,0, item);

    QTableWidgetItem *item1 = new QTableWidgetItem(from);
    ui->tableWidget->setItem(0,2, item1);

    QTableWidgetItem *item2 = new QTableWidgetItem(to);
    ui->tableWidget->setItem(0,3, item2);

    QTableWidgetItem *item3 = new QTableWidgetItem(date.toString());
    ui->tableWidget->setItem(0,4, item3);

    QTableWidgetItem *item4 = new QTableWidgetItem(time.toString());
    ui->tableWidget->setItem(0,5, item4);

//printf("num = %d\n",num);

//printf("s=%c\n",s);

//printf("from=%s\n",from.toStdString().data() );

//printf("to=%s\n",to.toStdString().data());

//printf("date=%s, time=%s\n",date.toString().toStdString().data(),time.toString().toStdString().data() );



}
