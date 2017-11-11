#include "finddialog.h"
#include <QGridLayout>
#include <QHBoxLayout>

FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{

    EditWhat = new QLineEdit("Walter");
    label = new QLabel("Find &What:");
    MatchCaseCBox = new QCheckBox("Match &case");
    SearchBackwardCBox = new QCheckBox("Search &backward");
    Findbtn = new QPushButton("&Find");
    Closebtn = new QPushButton("Close");


    QGridLayout *lay2 = new QGridLayout;
    lay2->addWidget(label,0,0);
    lay2->addWidget(EditWhat,0,1);
    lay2->addWidget(MatchCaseCBox,1,0,1,2);
    lay2->addWidget(SearchBackwardCBox,2,0,1,2);

    QVBoxLayout *lay3 = new QVBoxLayout;
    lay3->addWidget(Findbtn);
    lay3->addWidget(Closebtn);
    lay3->addStretch();

    QHBoxLayout *lay = new QHBoxLayout;
    lay->addLayout(lay2);
    lay->addLayout(lay3);

    this->setLayout(lay);

    setFixedSize(sizeHint());

}
