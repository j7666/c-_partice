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
#include <QToolBox>
#include <QDirModel>
#include <QSortFilterProxyModel>
#include <QComboBox>


class CurrencyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CurrencyModel(QWidget *parent = 0);
    ~CurrencyModel();
    void setCurrencyData(const QMap<QString, double> &map);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QString currencyAt(int offset) const;
    QMap<QString, double> CurrencyMap;
};

class CurrencyDlg : public QDialog
{
    Q_OBJECT
public:
    CurrencyDlg(QWidget *parent = 0);
    ~CurrencyDlg();

    QTableView *pView;
    QAbstractTableModel *pModel;


};


class ColorNameDialog : public QDialog
{
    Q_OBJECT
public:
    ColorNameDialog(QWidget *parent = 0);
    ~ColorNameDialog();
    enum weekday{monday = 0,tue,wed,thu,fri,sat,sun };

public slots:
    void reapplyFilter();
    void test();

private:
    QStringListModel *sourceModel;
    QListView *pListView;
    QSortFilterProxyModel *pSortFilterModel;

    QLineEdit *pFilterEdit;
    QLabel *pFilterLabel;
    QComboBox *pSyntaxCombox;
    QLabel *psyntaxLabel;

};

class DirectoryViewer :public QDialog
{
    Q_OBJECT
public:
    DirectoryViewer(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DirectoryViewer();
private:
    QDirModel *model;
    QTreeView *view;
    QPushButton *CreatedirectoryBtn;
    QPushButton *RemoveBtn;
    QPushButton *QuitBtn;

public slots:
    void onCreate();
    void onRemove();

};


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
         void createLeftWidget();


    private:
        //QDockWidget *m_dockwidget;
         Ticker *ticker;
         QTableWidget *mailListTable;
         QTextEdit *mailTextEdit;
         QTreeWidget *mailTreeWidget;
         QSplitter *mainsplit;
         QSplitter *rightSpliter;
         QListWidget *mainListWidget;
         QToolBox *leftToolBox;


    private:
          void createData();
          void mailListTableConstrucer();
          QIcon IconForSymbol(int id);
          QMap<int,QString> m_SymbolMap;
    public slots:
          void TeamLeaderDialog();
          void onSettingViwer();
          void onDirectoryViewer();
          void onColorNameDlg();
          void onCurrencles();

    };







#endif // WIDGET_H
