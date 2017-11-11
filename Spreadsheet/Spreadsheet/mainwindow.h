#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QMenu>

#include "spreadsheet.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initActions();
    void initMenu();
    void initTool();

private:
    Spreadsheet *spreadsheet;

    QAction *ActionNew;
    QAction *ActionOpen;
    QAction *ActionSave;
    QAction *ActionSaveAs;
    QActionGroup *ActionGroupRecentFile;
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
    void slotAutoRecalculate();

    void slotAbout();
    void slotAboutQt();


};

#endif // MAINWINDOW_H
