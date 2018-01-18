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


class SettingViewerDlg:public QDialog
    {
        Q_OBJECT
    public:
        SettingViewerDlg(QWidget *parent=0);
        ~SettingViewerDlg();
    public slots:


    private:
        QTreeWidget *pTreeWidget;
        QPushButton *addBtn;
        QPushButton *deletBtn;
//        QPushButton *okBtn;
//        QPushButton *cancelBtn;
//        QStringListModel *pModel;

    public slots:
        void onAddBtn();
        void ondeletBtn();
    };

class SettingViewer : public QTreeWidget
    {
        Q_OBJECT
    public:
        SettingViewer(QWidget *parent = 0);
        ~SettingViewer();
    };

class MailTableWidget : public QTableWidget
    {
        Q_OBJECT
    public:
        MailTableWidget(QWidget *parent );
        MailTableWidget(int rows, int columns, QWidget *parent = 0);
        ~MailTableWidget();

        void dragEnterEvent(QDragEnterEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);
        void dropEvent(QDropEvent *event);
    };

class SymbolListWidget : public QListWidget
    {
        Q_OBJECT
    public:

      SymbolListWidget(QWidget *parent =0);
      ~SymbolListWidget();
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *e);
      void dragMoveEvent(QDragMoveEvent *e);

      void performDrag();
private:
      QPoint startPos;
    };

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
          void onSettingViwer();

    };







#endif // WIDGET_H
