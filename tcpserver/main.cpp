#include <QCoreApplication>
#include <iostream>
#include <QTcpServer>
#include "tcpreceive.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "======TCP server======" << endl;

    tcpreceive tcpserver;

    return a.exec();
}
