#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QDockWidget>
#include <QWidget>
#include <QSplitter>
#include <QLabel>
#include <QTableWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>
#include <QPainter>
#include <QMap>
#include <QStringListModel>

class TeamLeaderDlg:public QDialog
    {
        Q_OBJECT
    public:
        TeamLeaderDlg(QWidget *parent=0);
        ~TeamLeaderDlg();
    public slots:
        void insert();
        void del();
    private:
        QListView *pview;
        QPushButton *insertBtn;
        QPushButton *deletBtn;
        QPushButton *okBtn;
        QPushButton *cancelBtn;
        QStringListModel *pModel;
    };


class Ticker :public QLabel
    {
        Q_OBJECT

    public:

        explicit Ticker(QWidget *parent=0, Qt::WindowFlags f=0);
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);
        void showEvent(QShowEvent *);
        void hideEvent(QHideEvent *);


    private:
        int myTimerId;
        int offset;


    };

class Widget : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Widget(QWidget *parent = 0);
        ~Widget();
         bool event(QEvent *event);
         bool eventFilter(QObject *object, QEvent *event);\
         void dragEnterEvent(QDragEnterEvent *dragEnterEvent);
         void dropEvent(QDropEvent *event);
         bool readfile(const QString &filename);

    private:
        //QDockWidget *m_dockwidget;
         Ticker *ticker;
         QTableWidget *mailListTable;
         QTextEdit *mailTextEdit;
         QTreeWidget *mailTreeWidget;
         QSplitter *mainsplit;
         QSplitter *rightSpliter;
         QListWidget *mainListWidget;

    private:
          void createData();
          void mailListTableConstrucer();
          QIcon IconForSymbol(int id);
          QMap<int,QString> m_SymbolMap;
    public slots:
          void TeamLeaderDialog();

    };







#endif // WIDGET_H
