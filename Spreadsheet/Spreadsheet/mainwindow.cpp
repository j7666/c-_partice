#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include "finddialog.h"
#include "gotocell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initActions();
    initMenu();
    initTool();

    spreadsheet = new Spreadsheet(this);
    setCentralWidget(spreadsheet);

    resize(800,600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initActions()
{
    ActionNew = new QAction(tr("New"),this);
    ActionNew->setIcon(QPixmap(":/images/filenew.png"));
    connect(ActionNew, SIGNAL(triggered()),this,SLOT(slotNewFile()));

    ActionOpen = new QAction(tr("Open"), this);
    ActionOpen->setIcon(QPixmap(":/images/fileopen.png"));
    connect(ActionOpen, SIGNAL(triggered()), this, SLOT(slotOpenFile()) );

    ActionSave = new QAction(tr("Save"), this);
    ActionSave->setIcon(QPixmap(":/images/filesave.png"));
    connect(ActionSave, SIGNAL(triggered()), this, SLOT(slotSaveFile()) );

    ActionSaveAs = new QAction(tr("Save As"), this );
    ActionSaveAs->setIcon(QPixmap(":/images/filesave.png"));
    connect(ActionSaveAs, SIGNAL(triggered()), this, SLOT(slotSaveAsFile()) );

    ActionGroupRecentFile = new QActionGroup(this);
    connect(ActionGroupRecentFile, SIGNAL(triggered(QAction*)), this, SLOT(slotRecentFile()) );

    ActionExit = new QAction(tr("exit"), this);
    connect(ActionExit, SIGNAL(triggered()), this, SLOT(slotExit()) );

    ActionCut = new QAction(tr("Cut"), this);
    connect(ActionCut, SIGNAL(triggered()), this, SLOT(slotCut()) );

    ActionCopy = new QAction(tr("Copy"), this);
    connect(ActionCopy, SIGNAL(triggered()), this, SLOT(slotCopy()) );

    ActionPaste = new QAction(tr("Paste"), this);
    connect(ActionPaste, SIGNAL(triggered()), this, SLOT(slotPaste()) );

    ActionDelete = new QAction(tr("Delete"), this);
    connect(ActionDelete, SIGNAL(triggered()), this, SLOT(slotDelete()) );


    ActionSelectRow = new QAction(tr("Row"), this);
    connect(ActionSelectRow, SIGNAL(triggered()), this, SLOT(slotSelectRow()) );

    ActionSelectColumn = new QAction(tr("Column"), this);
    connect(ActionSelectColumn, SIGNAL(triggered()), this, SLOT(slotSelectColumn()) );

    ActionSelectAll = new QAction(tr("All"), this);
    connect(ActionSelectAll, SIGNAL(triggered()), this, SLOT(slotSelectAll()) );

    ActionFind = new QAction(tr("Find"), this);
    connect(ActionFind, SIGNAL(triggered()), this, SLOT(slotFind()) );

    ActionGoToCell = new QAction(tr("Go to Cell"), this);
    connect(ActionGoToCell, SIGNAL(triggered()), this, SLOT(slotGoToCell()) );


    ActionRecalute = new QAction(tr("Recalculate"), this);
    connect(ActionRecalute, SIGNAL(triggered()), this, SLOT(slotRecalculate()) );

    ActionSort = new QAction(tr("Sort"), this);
    connect(ActionSort, SIGNAL(triggered()), this, SLOT(slotSort()) );

    ActionShowGrid = new QAction(tr("Show Grid"), this);
    ActionShowGrid->setCheckable(true);
    ActionShowGrid->setChecked(true);
    connect(ActionShowGrid, SIGNAL(triggered(bool)), this, SLOT(slotShowGrid(bool)) );

    ActionAutoRecalculate = new QAction(tr("Auto-Recalculate"), this);
    ActionAutoRecalculate->setCheckable(true);
    connect(ActionAutoRecalculate, SIGNAL(triggered()), this, SLOT(slotAutoRecalculate()) );

    ActionAbout = new QAction(tr("About"), this);
    connect(ActionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()) );

    ActionAboutQt = new QAction(tr("About Qt"), this);
    connect(ActionAboutQt, SIGNAL(triggered()), this, SLOT(slotAboutQt()) );



}

void MainWindow::initMenu()
{
    MenuFile = menuBar()->addMenu(tr("File"));
    MenuFile->addAction(ActionNew);
    MenuFile->addAction(ActionOpen);
    MenuFile->addAction(ActionSave);
    MenuFile->addAction(ActionSaveAs);
    MenuFile->addSeparator();
    //MenuFile->addSeparator();
    //MenuFile->addAction(ActionGroupRecentFile);
    MenuFile->addAction(ActionExit);


    MenuEdit = menuBar()->addMenu(tr("Edit"));
    MenuEdit->addAction(ActionCut);
    MenuEdit->addAction(ActionCopy);
    MenuEdit->addAction(ActionPaste);
    MenuEdit->addAction(ActionDelete);

    SubMenuSelect = MenuEdit->addMenu(tr("Select"));
    SubMenuSelect->addAction(ActionSelectRow);
    SubMenuSelect->addAction(ActionSelectColumn);
    SubMenuSelect->addAction(ActionSelectAll);
    MenuEdit->addSeparator();
    MenuEdit->addAction(ActionFind);
    MenuEdit->addAction(ActionGoToCell);

    MenuTools = menuBar()->addMenu(tr("Tools"));
    MenuTools->addAction(ActionRecalute);
    MenuTools->addAction(ActionSort);

    MenuOptions = menuBar()->addMenu(tr("Options"));
    MenuOptions->addAction(ActionShowGrid);
    MenuOptions->addAction(ActionAutoRecalculate);


    MenuHelp = menuBar()->addMenu(tr("Help"));
    MenuHelp->addAction(ActionAbout);
    MenuHelp->addAction(ActionAboutQt);

}

void MainWindow::initTool()
{
    //toolbar = addToolBar(tr("File"));
    toolbar = new QToolBar(this); //new的会挡住menubar
    toolbar->addAction(ActionNew);
    toolbar->addAction(ActionOpen);
    toolbar->addAction(ActionSave);
    toolbar->addSeparator();
    toolbar->addAction(ActionCut);
    toolbar->addAction(ActionCopy);
    toolbar->addAction(ActionPaste);

    addToolBar(Qt::TopToolBarArea, toolbar);

}

void MainWindow::slotNewFile()
{
    QMessageBox::information(this, "TEST", "NEW FILE");
}

void MainWindow::slotOpenFile()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "", QString("spreadsheet(*.sp,*.sps)"));
    //按照格式读取文件。
}

void MainWindow::slotSaveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "D:", QString("spreadsheet(*.sp,*.sps)") );
    //按照格式写文件。
}

void MainWindow::slotSaveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save AS"), "D:", QString("spreadsheet(*.sp,*.sps)") );
    //按照格式写文件。
}

void MainWindow::slotRecentFile()
{

}

void MainWindow::slotExit()
{
    //判断是否有修改，如果无修改，弹窗提示：确认退出。如果有修改，弹窗提示：是否需要保存。
    close();
}

void MainWindow::slotCut()
{
    spreadsheet->cut();
}

void MainWindow::slotCopy()
{
    spreadsheet->copy();
}

void MainWindow::slotPaste()
{
    spreadsheet->paste();
}

void MainWindow::slotDelete()
{
    spreadsheet->del();
}

void MainWindow::slotSelectRow()
{
    spreadsheet->selectrow();
}

void MainWindow::slotSelectColumn()
{
    spreadsheet->selectcolumn();
}

void MainWindow::slotSelectAll()
{
    spreadsheet->selectAll();
}



void MainWindow::slotFind()
{
    FindDialog dialog;
    dialog.exec();
}

void MainWindow::slotGoToCell()
{
    GotoCell gotocell;
    gotocell.exec();
}

void MainWindow::slotRecalculate()
{

}

void MainWindow::slotSort()
{

}

void MainWindow::slotShowGrid(bool checked)
{
    //QMessageBox::information(0, "" , QString::number(checked));
     spreadsheet->setShowGrid(checked);
}

void MainWindow::slotAutoRecalculate()
{

}

void MainWindow::slotAbout()
{

}

void MainWindow::slotAboutQt()
{

}
