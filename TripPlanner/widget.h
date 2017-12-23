#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

struct messagestuct
{
       quint16 num;
       QString s;
       QString From;
       QString To;
       QString Date;
       QString time;
};



namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void ConnectToServer();
    void SendRequest();
    void init();

private slots:
    void Search();
    void StopSearch();
    void Quit();
    void readData();

private:
    Ui::Widget *ui;
    QTcpSocket tcpsocket;



};

#endif // WIDGET_H
