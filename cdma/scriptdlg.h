#ifndef SCRIPTDLG_H
#define SCRIPTDLG_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>


class scriptDlg : public QDialog
{
    Q_OBJECT
public:
    explicit scriptDlg(QWidget *parent = 0);
    QString SQL;
    bool isLogin;
signals:


public slots:
    void onOkbtnClicked();
    void onCancelbtnClicked();
private:
    QLabel *label0;
    QTextEdit *scriptEditSql;
    QPushButton *okBtn;
    QPushButton *cancelBtn;


};

#endif // SCRIPTDLG_H
