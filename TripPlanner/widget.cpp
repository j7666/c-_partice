#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButtonSearch,SIGNAL(clicked(bool)),this,SLOT(Search()) );
    connect(ui->pushButtonStop,SIGNAL(clicked(bool)),this,SLOT(StopSearch()) );
    connect(ui->pushButtonQuit,SIGNAL(clicked(bool)),this,SLOT(Quit()) );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::Search()
{

}

void Widget::StopSearch()
{

}

void Widget::Quit()
{

}
