#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>


class loginDlg : public QDialog
    {
        Q_OBJECT
    public:
        explicit loginDlg(QWidget *parent = 0);

        QString userid;
        QString passwd;
        QString hostip;
        QString dbname;
        bool isLogin;

        
    private:
        QLineEdit *lineEditUserID;
        QLineEdit *lineEditPassword;
        QLineEdit *lineEditHostIp;
        QLineEdit *lineEditDbName;

        QPushButton *loginBtn;
        QPushButton *logoutBtn;

        QLabel *label0,*label1,*label2,*label3;



    private slots:
        void loginBtnClicked();
        void logoutBtnClicked();



    signals:
        
    public slots:
        
    };

#endif // LOGINDLG_H
