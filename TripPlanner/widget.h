#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
    {
        Q_OBJECT

    public:
        explicit Widget(QWidget *parent = 0);
        ~Widget();

    private slots:
        void Search();
        void StopSearch();
        void Quit();

    private:
        Ui::Widget *ui;
        QTcpSocket tcpsocket;

    };

#endif // WIDGET_H
