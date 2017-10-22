#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QFile>
#include "treemodel.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setupUi(this);

    QStringList headers;
    headers << tr("Title") << tr("Description");

    QFile file("H:/practice/test/cdma/cplusplus-practice.git/trunk/editabletreemodel/editabletreemodel/default.txt");
    file.open(QIODevice::ReadOnly);
    treemodel *model = new treemodel(headers, file.readAll());

    file.close();


    treeView->setAlternatingRowColors(true);

    treeView->setModel(model);
    for(int col = 0; col < model->columnCount(); ++col)
    {
        treeView->resizeColumnToContents(col);
    }


}

MainWindow::~MainWindow()
{
    //delete ui;
}
