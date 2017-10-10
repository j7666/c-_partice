#include "widget.h"
#include <QIcon>
#include "toolbox1.h"
#include <QHBoxLayout>




Widget::Widget(const QIcon icon, int ID, QString name, toolbox1 *w, QWidget *parent): QWidget(parent)
    {
        userID = ID;
        username = name;
        main_w = w;
        setWindowTitle(name);
        setWindowIcon(icon);

        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
        setAutoFillBackground(true);
        QPalette palette;
        palette.setColor(QPalette::Background,QColor(Qt::darkCyan) );
        setPalette(palette);
        init_widget();
    }

Widget::~Widget()
{

    }

void Widget::init_widget()
    {
        textBrowser = new QTextBrowser;

        textBrowser->setStyleSheet("background-image: url(:/images/2.jpg);");
        QHBoxLayout *layout1 = new QHBoxLayout;
        layout1->addWidget(textBrowser );

        fontComboBox = new QFontComboBox;
        fontComboBox->setToolTip("font set");
        //layout1.addWidget(fontComboBox );

        comboBox = new QComboBox;
        comboBox->setToolTip("font size");
        comboBox->setEditable(true);
        comboBox->addItem(QString::number(8) );
        comboBox->addItem(QString::number(9) );
        comboBox->addItem(QString::number(10) );
        comboBox->addItem(QString::number(11) );
        comboBox->addItem(QString::number(12) );
        comboBox->addItem(QString::number(13) );
        comboBox->addItem(QString::number(14) );
        comboBox->addItem(QString::number(15) );
        comboBox->addItem(QString::number(16) );
        comboBox->addItem(QString::number(17) );
        comboBox->addItem(QString::number(18) );
        comboBox->addItem(QString::number(19) );
        comboBox->addItem(QString::number(20) );
        comboBox->addItem(QString::number(21) );
        comboBox->addItem(QString::number(22) );
        comboBox->setCurrentIndex(4);

        toolBtn_1 = new QToolButton;
        toolBtn_1->setToolTip("jia cu");
        toolBtn_1->setIcon(QIcon(":/images/bold.png"));
        toolBtn_1->setCheckable(true);
        toolBtn_1->setAutoRaise(true);
        toolBtn_1->setText("jia cu ~");

        toolBtn_2 = new QToolButton;
        toolBtn_2->setToolTip("qing xie");
        toolBtn_2->setIcon(QIcon(":/images/italic.png"));
        toolBtn_2->setCheckable(true);
        toolBtn_2->setAutoRaise(true);
        toolBtn_2->setText("qing xie ~");

        toolBtn_3 = new QToolButton;
        toolBtn_3->setToolTip("xia hua xiang");
        toolBtn_3->setIcon(QIcon(":/images/under.png"));
        toolBtn_3->setCheckable(true);
        toolBtn_3->setAutoRaise(true);
        toolBtn_3->setText("xia hua xiang ~");

        toolBtn_4 = new QToolButton;
        toolBtn_4->setToolTip("yan se");
        toolBtn_4->setIcon(QIcon(":/images/color.png"));
        toolBtn_4->setCheckable(true);
        toolBtn_4->setAutoRaise(true);
        toolBtn_4->setText("yan se ~");


        toolBtn_5 = new QToolButton;
        toolBtn_5->setAutoRaise(true);
        toolBtn_5->setText("zhu chuang kou ~");

        QHBoxLayout *layout2 = new QHBoxLayout;
        layout2->addWidget(this->fontComboBox );
        layout2->addWidget(this->comboBox );
        layout2->addWidget(this->toolBtn_1 );
        layout2->addWidget(this->toolBtn_2 );
        layout2->addWidget(this->toolBtn_3 );
        layout2->addWidget(this->toolBtn_4 );
        layout2->addWidget(this->toolBtn_5 );


        lineEdit = new QLineEdit;
        pushBtn = new QPushButton;
        pushBtn->setText("Send");

        QHBoxLayout *layout3 = new QHBoxLayout;
        layout3->addWidget(this->lineEdit);
        layout3->addWidget(this->pushBtn);

        QVBoxLayout *layout4 = new QVBoxLayout;
        layout4->addLayout(layout1);
        layout4->addLayout(layout2);
        layout4->addLayout(layout3);
        setLayout(layout4);

        textBrowser->setCurrentFont( this->fontComboBox->font() );
        textBrowser->setFontPointSize(this->comboBox->currentText().toDouble());


        lineEdit->setFocus();



    }
