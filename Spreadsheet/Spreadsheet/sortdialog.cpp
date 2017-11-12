#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);
    ui->SecondarygroupBox->hide();
    ui->TertiarygroupBox->hide();
    ui->MorepushButton->setCheckable(true);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    connect(ui->OKpushButton,SIGNAL(clicked()),this,SLOT(SlotOkBtnClicked()));
    connect(ui->CancelpushButton,SIGNAL(clicked()),this,SLOT(reject()));
    //connect(ui->MorepushButton,SIGNAL(toggled(bool)),this,SLOT(SlotMore(bool)));
    connect(ui->MorepushButton,SIGNAL(toggled(bool)),ui->SecondarygroupBox,SLOT(setVisible(bool)));
    connect(ui->MorepushButton,SIGNAL(clicked(bool)),ui->TertiarygroupBox,SLOT(setVisible(bool)));

    setColumnRange('A','Z');
}

SortDialog::~SortDialog()
{
    delete ui;
}

void SortDialog::setColumnRange(QChar first,QChar last)
{
    QChar ch = first;
        while(ch <= last)
    {
        ui->PrimaryColumncomboBox->addItem(QString(ch));
        ui->SecondaryColumncomboBox->addItem(QString(ch));
        ui->TertiaryColumncomboBox->addItem(QString(ch));
        ch = ch.unicode()+1;
    }

}

void SortDialog::SlotOkBtnClicked()
{
    cPrimaryColumn = ui->PrimaryColumncomboBox->currentText();
    cSecondColumn = ui->SecondaryColumncomboBox->currentText();
    cTertiaryColumn = ui->TertiaryColumncomboBox->currentText();

    bPrimaryOrder = ui->PrimaryOrdercomboBox->currentIndex();
    bSecondOrder = ui->SecondaryOrdercomboBox->currentIndex();
    bTertiaryOrder = ui->TertiaryOrdercomboBox->currentIndex();

    accept();
}


