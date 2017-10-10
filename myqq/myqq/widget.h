#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QLineEdit>
#include <QColor>

class toolbox1;

class Widget : public QWidget
    {
        Q_OBJECT

    public:
        Widget(const QIcon icon, int ID,QString username,toolbox1 *w, QWidget *parent = 0);
        ~Widget();
        QPushButton *pushBtn;

    private:
        QTextBrowser *textBrowser;
        QFontComboBox *fontComboBox;
        QComboBox *comboBox;
        QToolButton *toolBtn_1;
        QToolButton *toolBtn_2;
        QToolButton *toolBtn_3;
        QToolButton *toolBtn_4;
        QToolButton *toolBtn_5;

        QLineEdit *lineEdit;

        int userID;
        QString username;

        toolbox1 *main_w;

        void init_widget();
    };

#endif // WIDGET_H
