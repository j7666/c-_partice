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

    connect(treeView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(updateActions()));

    connect(actionInsert_Child,SIGNAL(triggered()),this,SLOT(insertChild()));
    connect(actionInsert_Colunm, SIGNAL(triggered()), this, SLOT(insertColumn()));
    connect(actionInsert_Row, SIGNAL(triggered()),this, SLOT(insertRow()));
    connect(actionRemove_Colunm, SIGNAL(triggered()),this,SLOT(removeColumn()));
    connect(actionRemove_Row, SIGNAL(triggered()), this, SLOT(removeRow()));
    connect(actionExit,SIGNAL(triggered()),this,SLOT(close()));

    updateActions();

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::updateActions()
{
    bool hasSelection = !treeView->selectionModel()->selection().isEmpty();
    actionRemove_Colunm->setEnabled(hasSelection);
    actionRemove_Row->setEnabled(hasSelection);

    bool hasCurrent = treeView->selectionModel()->currentIndex().isValid();
    actionInsert_Colunm->setEnabled(hasCurrent);
    actionInsert_Row->setEnabled(hasCurrent);

    if(hasCurrent)
    {
        treeView->closePersistentEditor(treeView->selectionModel()->currentIndex() );
        int row = treeView->selectionModel()->currentIndex().row();
        int col = treeView->selectionModel()->currentIndex().column();
        if(treeView->selectionModel()->currentIndex().parent().isValid())
            QMainWindow::statusBar()->showMessage(tr("Position:(%1,%2)").arg(row).arg(col));
        else
            QMainWindow::statusBar()->showMessage(tr("Position:(%1,%2) in top level").arg(row).arg(col));
    }
}

void MainWindow::insertChild()
{
    QModelIndex index = this->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();

    if(model->columnCount(index) == 0 ) //如果一列都没有。即列为0；首先插入一列。
    {
        if(!model->insertColumn(0, index))
                return;
    }

    if(!model->insertRow(0,index) )
        return;


    for(int col = 0; col < model->columnCount(); ++col)
    {
        QModelIndex childindex = model->index(0, col, index);
        model->setData(childindex, "[No Data]", Qt::EditRole);

        if(!model->headerData(col,Qt::Horizontal).isValid())
            model->setHeaderData(col,Qt::Horizontal,QVariant("[NoData]"),Qt::EditRole);
    }

    treeView->selectionModel()->setCurrentIndex(model->index(0,0,index), QItemSelectionModel::ClearAndSelect );
}

bool MainWindow::insertColumn(const QModelIndex &parent)
{

}

void MainWindow::insertRow()
{

}

bool MainWindow::removeColumn(const QModelIndex &parent)
{

}

void MainWindow::removeRow()
{

}
