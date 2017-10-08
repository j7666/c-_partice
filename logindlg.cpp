#include "logindlg.h"
#include <QGridLayout>
#include <QPalette>
#include <QMessageBox>

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent)
    {
        isLogin = false; //开始没有登录，值为false。
        setWindowTitle(tr("login"));

        label0 = new QLabel(QString("UserID"),this);
        label1 = new QLabel(QString("Passwd"),this);
        label2 = new QLabel(QString("DbName"),this);
        label3 = new QLabel(QString("HostIp"),this);

        lineEditUserID = new QLineEdit(this);
        lineEditPassword = new QLineEdit(this);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        lineEditDbName = new QLineEdit(this);
        lineEditHostIp = new QLineEdit(this);


        loginBtn = new QPushButton(this);
        logoutBtn = new QPushButton(this);

        loginBtn->setText(QString("login"));
        logoutBtn->setText(QString("logout"));

        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(label0,0,0);
        layout->addWidget(label1,1,0);
        layout->addWidget(label2,2,0);
        layout->addWidget(label3,3,0);

        layout->addWidget(lineEditUserID,0,1);
        layout->addWidget(lineEditPassword,1,1);
        layout->addWidget(lineEditDbName,2,1);
        layout->addWidget(lineEditHostIp,3,1);

        layout->addWidget(loginBtn,4,0);
        layout->addWidget(logoutBtn,4,1);

        layout->setColumnStretch(0,1);
        layout->setColumnStretch(1,1);
        layout->setMargin(15);
        layout->setSpacing(10);

        layout->setSizeConstraint(QLayout::SetFixedSize);

        setAutoFillBackground(true);

        QPalette palette;
        palette.setBrush(QPalette::Background,QBrush(QPixmap(":/png/2.jpg")));
        setPalette(palette);

        connect(loginBtn,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
        connect(logoutBtn,SIGNAL(clicked()),this,SLOT(logoutBtnClicked()));


}

void loginDlg::loginBtnClicked()
{
    userid = lineEditUserID->text();
    passwd = lineEditPassword->text();
    dbname = lineEditDbName->text();
    hostip = lineEditHostIp->text();
    isLogin = true;
    close();
}

void loginDlg::logoutBtnClicked()
{
        close();
}
