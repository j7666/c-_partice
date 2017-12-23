#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec );
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    printf("tcp client\n");
    Widget w;
    w.show();

    return a.exec();
}
