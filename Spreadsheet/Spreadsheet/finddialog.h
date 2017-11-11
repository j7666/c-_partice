#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

class FindDialog : public QDialog
    {
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

    };

#endif // FINDDIALOG_H
