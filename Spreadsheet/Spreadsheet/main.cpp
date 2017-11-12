#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <qDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv) ;

    QTranslator t;
    t.load(":/Spreadsheet_Zh_CN" );
    //qDebug()<< QLocale::system().name();

    a.installTranslator(&t);
    MainWindow w;

    w.show();
    
    return a.exec();
}
