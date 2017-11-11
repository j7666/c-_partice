#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

class FindDialog
    {
    public:
        FindDialog();
        bool isMatchCase;
        bool isSearchBackward;
        QDialog dialog;
    private:
        QPushButton *Findbtn;
        QPushButton *Closebtn;
        QLabel *label;
        QCheckBox *MatchCaseCBox;
        QCheckBox *SearchBackwardCBox;
        QLineEdit *EditWhat;

    };

#endif // FINDDIALOG_H
