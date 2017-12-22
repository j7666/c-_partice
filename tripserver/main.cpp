#include <QCoreApplication>
#include <tripserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tripserver ts;
    printf("===Tcp Server Runing===\n");

    return a.exec();
}
