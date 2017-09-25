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
        
    signals:

        
    public slots:
    private:
        QLabel *label0;
        QTextEdit *scriptEditSql;
        QPushButton *okBtn;
        QPushButton *cancelBtn;
        
    };

#endif // SCRIPTDLG_H
