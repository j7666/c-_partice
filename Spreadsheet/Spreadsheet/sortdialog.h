#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>

namespace Ui {
class SortDialog;
}

class SortDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SortDialog(QWidget *parent = 0);
    ~SortDialog();
    void setColumnRange(QChar first, QChar last);

    QString cPrimaryColumn;
    bool bPrimaryOrder;

    QString cSecondColumn;
    bool bSecondOrder;

    QString cTertiaryColumn;
    bool bTertiaryOrder;
    
private:
    Ui::SortDialog *ui;



private slots:
    void SlotOkBtnClicked();
};

#endif // SORTDIALOG_H
