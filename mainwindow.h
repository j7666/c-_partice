#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QMdiArea>


class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void closeEvent(QCloseEvent *event);



    private:
        void CreatMenus();
        void CreatActions();
        void showSub();
        void showview();

        QMenu *adminMenu;
        QMenu *dataMenu;
        QMenu *windowMenu;
        QMenu *helpMenu;


        QAction *loginAction;
        QAction *logoutAction;
        QAction *exitAction;

        QAction *scriptAction;

        QAction *cascadeAction;
        QAction *tileAction;

        QAction *aboutAction;

        QMdiArea *mdiArea;


    private slots:

        void on_login();
        void on_logout();
        void on_exit();
        void on_script();
        void cascadeSubWindows();
        void tileSubWindows();
        void on_about();




    };

#endif // MAINWINDOW_H
