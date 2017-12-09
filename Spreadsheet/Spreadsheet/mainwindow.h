#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QMenu>

#include "spreadsheet.h"
#include "finddialog.h"
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initActions();
    void initMenu();
    void initTool();
    void initStatusbar();
    bool isModify() {return bIsModify;}
    void setModify(bool isModify) {bIsModify = isModify;}
    bool loadFile(const QString &strfilename);
    void updateRecentFiles(const QString &filename);
    void updateRecentActions();
    bool bAutoRecalc;
    void Savefile(const QString &filename);
    void closeEvent(QCloseEvent *);
    bool okToContinue();
private:
    Spreadsheet *spreadsheet;

    QAction *ActionNew;
    QAction *ActionOpen;
    QAction *ActionSave;
    QAction *ActionSaveAs;
    QAction *ActionRecentFile[5];
    QAction *ActionExit;

    QAction *ActionCut;
    QAction *ActionCopy;
    QAction *ActionPaste;
    QAction *ActionDelete;
    QAction *ActionSelect;
    QAction *ActionSelectRow;
    QAction *ActionSelectColumn;
    QAction *ActionSelectAll;
    QAction *ActionFind;
    QAction *ActionGoToCell;


    QAction *ActionRecalute;
    QAction *ActionSort;

    QAction *ActionShowGrid;
    QAction *ActionAutoRecalculate;

    QAction *ActionAbout;
    QAction *ActionAboutQt;

    //menu
    QMenu *MenuFile;
    QMenu *MenuEdit;
    QMenu *SubMenuSelect;
    QMenu *MenuTools;
    QMenu *MenuOptions;
    QMenu *MenuHelp;

    //Toolbar
    QToolBar *toolbar;

    //Statusbar
    //不能定义QStatusBar *statusBar 指针
    //否则会出现编译错误：error C2064: 项不会计算为接受 0 个参数的函数

    QLabel *label1;
    QLabel *label2;


    FindDialog *dialog;
    QString strCurrentFileName;
    bool bIsModify;
    QStringList Recentfiles;


private slots:
    void slotNewFile();
    void slotOpenFile();
    void slotSaveFile();
    void slotSaveAsFile();
    void slotRecentFile();
    void slotExit();

    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotDelete();
    void slotSelectRow();
    void slotSelectColumn();
    void slotSelectAll();
    void slotFind();
    void slotGoToCell();

    void slotRecalculate();
    void slotSort();

    void slotShowGrid(bool checked);

    void slotAbout();
    void slotAboutQt();

    void slotSpreadmodify();
    void slotUpdateStatusBar();




};

#endif // MAINWINDOW_H
