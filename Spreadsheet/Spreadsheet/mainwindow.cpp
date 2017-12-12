#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include "gotocell.h"
#include "sortdialog.h"
#include "spreadsheetcompare.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>



class SpreadsheetCompare;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    spreadsheet = new Spreadsheet(this);
    setCentralWidget(spreadsheet);
    dialog = NULL;
    bIsModify = false;
    setCurrentFile("");
    Recentfiles.clear();

    initActions();
    initMenu();
    initTool();
    initStatusbar();
    connect(spreadsheet,SIGNAL(modified()),this,SLOT(slotSpreadmodify()) );

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

    for(int i = 0; i < 5; i++)
    {
        ActionRecentFile[i] = new QAction(this);
        connect(ActionRecentFile[i], SIGNAL(triggered(bool)), this, SLOT(slotRecentFile()) );
        ActionRecentFile[i]->setVisible(false);
    }


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
    connect(ActionAutoRecalculate, SIGNAL(triggered(bool)), spreadsheet, SLOT(slotSetAutoRecalc(bool)) );

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
    for(int i = 0; i < 5; i++)
    {
        MenuFile->addAction(ActionRecentFile[i]);
    }

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

void MainWindow::initStatusbar()
{
    label1 = new QLabel("W999");
    label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label1->setMinimumSize(label1->sizeHint());
    label2 = new QLabel("TEST");

    QLabel *label3 = new QLabel("TEST");

    processBar = new QProgressBar;
    processBar->setTextVisible(false);
    processBar->setMaximum(0);
    processBar->setMinimum(100);


    statusBar()->addWidget(label1);
    statusBar()->addWidget(label2,1);

    statusBar()->addPermanentWidget(processBar);
        statusBar()->addPermanentWidget(label3);

    connect(spreadsheet,SIGNAL(currentCellChanged(int,int,int,int)),
            this,SLOT(slotUpdateStatusBar()));


}

bool MainWindow::loadFile(const QString &strfilename)
{
    if( !spreadsheet->readFile(strfilename) )
    {
        return false;
    }
    setModify(false);
    setCurrentFile(strfilename);
    return true;

}



void MainWindow::setCurrentFile(const QString &file)
{
    if(file.isEmpty())
    {
        QString strtitle = "untitled";
        setWindowTitle(strtitle);
        strCurrentFileName = "";
    }
    else
    {
        strCurrentFileName = file;
        setWindowTitle(QFileInfo(file).fileName());
    }


    updatewindowtitle();

    updateRecentFiles(strCurrentFileName);
}

void MainWindow::updateRecentFiles(const QString &filename)
{
        //move down
        //del chong fu
        //del wuxiao
    if(filename.isEmpty())
    {
        return;
    }
    Recentfiles.removeAll(filename);
    Recentfiles.prepend(filename);

    QStringListIterator iterator(Recentfiles );
    while(iterator.hasNext())
    {
        QString strfilename = iterator.next();
        if(!(QFile::exists(strfilename)))
            Recentfiles.removeOne(strfilename);
    }

    updateRecentActions();

}

void MainWindow::slotNewFile()
{
    if(okToContinue())
        spreadsheet->clear();
    setCurrentFile("");
    //setModify(true);
}

void MainWindow::slotOpenFile()
{
    if(!okToContinue())
    {
        return;
    }

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "", QString("spreadsheet(*.sp *.sps)"));
    if(filename.isEmpty())
    {
        return;
    }

    if(!loadFile(filename))
    {
        statusBar()->showMessage("Open file failed",1000);
        return;
    }

    statusBar()->showMessage("loadFile sucess",1000);

}

void MainWindow::slotSaveFile()
{
    if(!strCurrentFileName.isEmpty())
    {
        Savefile(strCurrentFileName);
    }else
        slotSaveAsFile();



}

void MainWindow::Savefile(const QString &filename)
{
   spreadsheet->writeFile(filename);
   statusBar()->showMessage("File Saved",1000);
   setModify(false);
   updatewindowtitle();

}

void MainWindow::closeEvent(QCloseEvent *)
{
    bool ret = false;
    if(isModify())
    {
        ret = QMessageBox::question(this,tr("warning"),"File is modify,do you want to save?",QString("Save"),QString("Don't Save"));
        if(!ret)
            slotSaveFile();
    }
    close();

}

bool MainWindow::okToContinue()
{
    if(isModify())
    {
        bool ret = QMessageBox::question(this,tr("warning"),"File is modify,do you want to save?",QString("Save"),QString("Don't Save"));
        if(!ret)
        slotSaveFile();
    }

    return true;

}

void MainWindow::updatewindowtitle()
{
    QString title = windowTitle();

    if(!isModify())  //no modify
    {
        if(!title.contains('*'))
            return;
        else
        {
            QString newtitle = title.remove('*');
            setWindowTitle(newtitle);
        }
    }
    else {
        if(title.contains('*'))
            return;
        else
        {
            QString newtitle = title + '*';
            setWindowTitle(newtitle);
        }
    }
}

void MainWindow::slotSaveAsFile()
{
        QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), "D:", QString("spreadsheet(*.sp,*.sps)") );
        if(!filename.isEmpty())
            Savefile(filename);
        setCurrentFile(filename);

}

void MainWindow::slotRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QString filename = action->text();
    if(okToContinue())
    {
        loadFile(filename);
    }
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
    if(!dialog)
    {
        dialog = new FindDialog(this);
        connect(dialog,SIGNAL(findPrevious(QString ,Qt::CaseSensitivity)),spreadsheet,SLOT(slotFindPrevious(QString ,Qt::CaseSensitivity)) );
        connect(dialog,SIGNAL(findNext(QString ,Qt::CaseSensitivity)),spreadsheet,SLOT(slotFindNext(QString ,Qt::CaseSensitivity)) );
    }

    dialog->show();
    dialog->raise();
    dialog->activateWindow();


}

void MainWindow::slotGoToCell()
{
    GotoCell gotocell(this);
    if(gotocell.exec())
    {
        QString str = gotocell.EditCellLocation->text().toUpper();
        //QMessageBox::information(0,"",str);
        spreadsheet->setCurrentCell(str.mid(1).toInt()-1, str[0].unicode()-'A' );
    }
}

void MainWindow::slotRecalculate()
{
    spreadsheet->AutoRecalculate();
}

void MainWindow::slotSort()
{
    SortDialog dlg;

    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dlg.setColumnRange('A'+range.leftColumn(),'A'+range.rightColumn());

    if(dlg.exec())
    {
        SpreadsheetCompare compare;
        compare.keys[0] = dlg.cPrimaryColumn.toInt();
        compare.keys[1] = dlg.cSecondColumn.toInt();
        compare.keys[2] = dlg.cTertiaryColumn.toInt();

        compare.ascending[0] = dlg.bPrimaryOrder;
        compare.ascending[1] = dlg.bSecondOrder;
        compare.ascending[2] = dlg.bTertiaryOrder;

        spreadsheet->sort(compare);
    }
    //QMessageBox::information(0,"",dlg.cPrimaryColumn);
    //QMessageBox::information(0,"",QString::number(dlg.bPrimaryOrder ));
}

void MainWindow::slotShowGrid(bool checked)
{
    //QMessageBox::information(0, "" , QString::number(checked));
    spreadsheet->setShowGrid(checked);
}


void MainWindow::slotAbout()
{
    QMessageBox::about(this,tr("about"),"jialw\n2017-11-22");
}

void MainWindow::slotAboutQt()
{
    QMessageBox::aboutQt(this,tr("about"));
}

void MainWindow::slotSpreadmodify()
{
//    if(strCurrentFileName.isEmpty())
//        return;
    setModify(true);
    updatewindowtitle();
    slotUpdateStatusBar();
}

void MainWindow::slotUpdateStatusBar()
{
    label1->setText(spreadsheet->currentLocation());
    label2->setText(spreadsheet->currentFormula() );
}

void MainWindow::updateRecentActions()
{
    for(int i = 0; i < 5; i++)
    {
        if(i < Recentfiles.size())
        {
        ActionRecentFile[i]->setText(Recentfiles[i]);
        ActionRecentFile[i]->setVisible(true);
        }
//        else
//            ActionRecentFile[i]

    }
}
