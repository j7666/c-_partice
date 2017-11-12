#ifndef GOTOCELL_H
#define GOTOCELL_H

#include <QDialog>
#include "ui_gotocelldialog.h"
#include <QString>

class GotoCell : public QDialog , public Ui_GotoCellDialog
{
    Q_OBJECT
public:
    explicit GotoCell(QWidget *parent = 0);
    
signals:
    
private slots:
    void EnableEditCellLoaction(QString str);
    
};

#endif // GOTOCELL_H
