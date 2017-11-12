#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QString>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
    bool isMatchCase;
    bool isSearchBackward;

    QPushButton *Findbtn;
    QPushButton *Closebtn;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
    QCheckBox *MatchCaseCBox;
    QCheckBox *SearchBackwardCBox;
    QLineEdit *EditWhat;


signals:
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
    void findNext(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void FindBtnClicked();


};

#endif // FINDDIALOG_H
