#include "logindlg.h"
#include "QGridLayout"
#include <QMessageBox>

loginDlg::loginDlg(QWidget *parent):QDialog(parent)
    {

        label1 = new QLabel;
        label1->setText("User ID");

        lineEditUserID = new QLineEdit;

        label2 = new QLabel;
        label2->setText("Passwd");
        lineEditPasswd = new QLineEdit;
        lineEditPasswd->setEchoMode(QLineEdit::Password);

        label3 = new QLabel;
        label3->setText("Computer IP");
        lineEditHostIP = new QLineEdit;

        label4 = new QLabel("Computer Port");
        lineEditHostPort = new QLineEdit;

        okBtn = new QPushButton("OK");
        cancelBtn = new QPushButton("Cancel");

        QGridLayout *layout1 = new QGridLayout(this);
        layout1->addWidget(label1,0,0);
        layout1->addWidget(this->lineEditUserID,0,1 );
        layout1->addWidget(label2,1,0);
        layout1->addWidget(this->lineEditPasswd,1,1);
        layout1->addWidget(label3,2,0);
        layout1->addWidget(this->lineEditHostIP,2,1);
        layout1->addWidget(label4,3,0);
        layout1->addWidget(this->lineEditHostPort,3,1);
        layout1->addWidget(this->okBtn,4,0);
        layout1->addWidget(this->cancelBtn,4,1);

        layout1->setMargin(10);
        layout1->setSpacing(10);
        layout1->setSizeConstraint(QLayout::SetFixedSize );

        setLayout(layout1);


        connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtnSlot()));
        connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBtnSlot()) );

        isLogin = false;

        setWindowIcon(QIcon(":/images/3.png"));
        lineEditUserID->setFocus();

        setWindowFlags(Qt::FramelessWindowHint);

        setAutoFillBackground(true);
        QPalette palette1;
        palette1.setBrush(QPalette::Background, QBrush(QPixmap(":/images/1.jpg")));

        setPalette(palette1);







    }

void loginDlg::okBtnSlot()
    {
        //
        if(lineEditUserID->text().isEmpty())
            {
                QMessageBox::information(this,"Warning","UserID Can't Empty");
                lineEditUserID->setFocus();
            }
        else
            {
                bool ok;
                userid = lineEditUserID->text().toInt(&ok);
                if(!ok)
                    {
                        QMessageBox::information(this,"Warning","UserID 0-255");
                        lineEditUserID->setFocus();
                    }
                else
                    {
                        isLogin = true;
                        passwd = lineEditPasswd->text();
                        hostip = lineEditHostIP->text();
                        hostport = lineEditHostPort->text().toInt();
                        close();
                    }

            }


    }

void loginDlg::cancelBtnSlot()
    {
        close();

    }
