#include "finddialog.h"
#include <QGridLayout>
#include <QHBoxLayout>

FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
   QDialog dlg;
   EditWhat = new QLineEdit;
   label = new QLabel;
   MatchCaseCBox = new QCheckBox;
   SearchBackwardCBox = new QCheckBox;
   Findbtn = new QPushButton;
   Closebtn = new QPushButton;

   QHBoxLayout *lay1;
   lay1->addWidget(label);
   lay1->addWidget(EditWhat);


   QVBoxLayout *lay2;
   lay2->addLayout(lay1);
   lay2->addWidget(MatchCaseCBox);
   lay2->addWidget(SearchBackwardCBox);

   QVBoxLayout *lay3;
   lay3->addWidget(Findbtn);
   lay3->addWidget(Closebtn);
   lay3->addStretch();

   QHBoxLayout *lay;
   lay->addLayout(lay2);
   lay->addLayout(lay3);

    dlg.setLayout(lay);
//   QGridLayout layout;
//   layout.addLayout(lay1,0,0);
//   layout.addWidget(MatchCaseCBox,1,0);
//   layout.addWidget(SearchBackwardCBox,1,0);

//   layout.addWidget(Findbtn,0,1);
//   layout.addWidget(Closebtn,2,1);





}
