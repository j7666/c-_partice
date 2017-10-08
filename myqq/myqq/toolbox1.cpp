#include "toolbox1.h"
#include <QIcon>

toolbox1::toolbox1(QWidget *parent) :
    QToolBox(parent)
{
    setWindowIcon(QIcon(":/images/3.png"));
}
