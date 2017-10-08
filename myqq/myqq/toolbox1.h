#ifndef TOOLBOX1_H
#define TOOLBOX1_H

#include <QToolBox>
#include <QToolButton>
#include "widget.h"

#define CLIENTCOUNT 256 //最大客户端数量

class toolbox1 : public QToolBox
{
    Q_OBJECT
public:
    explicit toolbox1(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QToolButton *toolBtn[CLIENTCOUNT];
    Widget *child[CLIENTCOUNT];
    
};

#endif // TOOLBOX1_H
