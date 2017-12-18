#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <qDebug>
#include <QSplashScreen>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv) ;

    QTranslator t;
    t.load(":/Spreadsheet_Zh_CN" );
    //qDebug()<< QLocale::system().name();

    a.installTranslator(&t);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":images/shuijiemian.png"));
    splash->show();

    QFont font("Times", 20 , QFont::Bold);
    splash->setFont(font);

    splash->showMessage("test",Qt::AlignBottom | Qt::AlignRight,Qt::white);

    MainWindow w;
    w.show();

    splash->finish(&w);
    delete splash;
    
    return a.exec();
}
