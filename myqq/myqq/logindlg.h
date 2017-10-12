#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "logindlg.h"


class loginDlg : public QDialog
    {

        Q_OBJECT
    public:
        explicit loginDlg(QWidget *parent = 0 );

        int userid;
        QString passwd;
        QString hostip;
        int hostport;
        bool isLogin;


    private:
        QLineEdit *lineEditUserID;
        QLineEdit *lineEditPasswd;
        QLineEdit *lineEditHostIP;
        QLineEdit *lineEditHostPort;




        QLabel *label1;
        QLabel *label2;
        QLabel *label3;
        QLabel *label4;

        QPushButton *okBtn;
        QPushButton *cancelBtn;
        loginDlg *dlg;



    private slots:
        void okBtnSlot();
        void cancelBtnSlot();



    };

#endif // LOGINDLG_H
