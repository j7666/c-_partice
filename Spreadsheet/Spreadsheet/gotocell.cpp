#include "gotocell.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QMessageBox>

GotoCell::GotoCell(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->YesbuttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp exp("[a-zA-Z][1-9][0-9]{0,2}");
    EditCellLocation->setValidator(new QRegExpValidator(exp,this) );

    connect(EditCellLocation,SIGNAL(textChanged(QString)),this,SLOT(EnableEditCellLoaction(QString)));
    connect(YesbuttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(YesbuttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

void GotoCell::EnableEditCellLoaction(QString &str)
{
    //YesbuttonBox->button(QDialogButtonBox::Ok)->setEnabled( EditCellLocation->hasAcceptableInput() );
    YesbuttonBox->button(QDialogButtonBox::Ok)->setEnabled( true );
    //QMessageBox::information(0,"",str);
}
