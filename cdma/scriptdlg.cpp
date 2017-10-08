#include "scriptdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>

scriptDlg::scriptDlg(QWidget *parent) :
    QDialog(parent)
    {
        isLogin = false;
        label0 = new QLabel("SQL");
        okBtn = new QPushButton("Exe");
        cancelBtn = new QPushButton("Cancel");
        scriptEditSql = new QTextEdit;

        QHBoxLayout *layout1 = new QHBoxLayout;  //不能设置父对象为this，否则窗口会只显示layout1
        QGridLayout *layout2 = new QGridLayout(this);
        layout2->addWidget(label0,0,0);
        layout2->addWidget(scriptEditSql,0,1);

        layout1->addWidget(okBtn);
        layout1->addWidget(cancelBtn);

        layout2->addLayout(layout1,1,1);

        //connect(okBtn,SIGNAL(clicked()),this,SLOT(on_Script()))
        connect(okBtn,SIGNAL(clicked()),this,SLOT(onOkbtnClicked()));
        connect(cancelBtn,SIGNAL(clicked()),this,SLOT(onCancelbtnClicked()));


}

void scriptDlg::onOkbtnClicked()
{
    SQL = scriptEditSql->toPlainText();
    isLogin = true;
    close();
}

void scriptDlg::onCancelbtnClicked()
{
    close();
}
