#include "widget.h"
#include <QUrl>
#include <QMapIterator>
#include <QToolBox>
#include <QStringListModel>
#include <QApplication>
#include <QTableWidgetItem>
#include <QInputDialog>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent)
{

    /******************QSplite用法********************/
    //右侧邮件列表和邮件内容显示区域
    mailListTable = new MailTableWidget(2,3);
//    for(int i =0;i <2;i++)
//    {
//        for(int j =0; j<3; j++)
//        {
//            QTableWidgetItem *item = new QTableWidgetItem;
//            mailListTable->setItem(i,j,item);
//        }

//    }
    mailListTable->verticalHeader()->setVisible(false);


    mailTextEdit = new QTextEdit("Mail context");
    mailTextEdit->setAcceptDrops(false);  //禁止textedit的拖放
    setAcceptDrops(true);  //启动主区域的拖放

    ticker = new Ticker;
    ticker->setBackgroundRole(QPalette::Text);

    ticker->setPalette(QPalette(QColor(Qt::green)));
    ticker->setText("123456789");

    rightSpliter = new QSplitter(Qt::Vertical);
    rightSpliter->addWidget(mailListTable );
    rightSpliter->addWidget(mailTextEdit );

    rightSpliter->addWidget(ticker);

    //左侧树状窗体
//    mailTreeWidget = new QTreeWidget;
//    mailTreeWidget->setColumnCount(2);
//    mailTreeWidget->setHeaderLabels(QStringList() << "name" << "value");
//    QTreeWidgetItem *countryItem= new QTreeWidgetItem(QStringList()<<"Country");
//    countryItem->setText(1,"People");
//    countryItem->setBackground(0,QBrush(QColor(Qt::green)));
//    countryItem->setForeground(1,QBrush(QColor(Qt::blue)));

//    mailTreeWidget->insertTopLevelItem(0,countryItem);
//    mailTreeWidget->insertTopLevelItem(0,new QTreeWidgetItem(countryItem,QStringList()<<"two" << "200") );

//    countryItem->insertChild(0,new QTreeWidgetItem(QStringList()<<"three" << "300"));
//    countryItem->setFlags(Qt::ItemIsSelectable |
//                          Qt::ItemIsEditable |
//                         // Qt::ItemIsDragEnabled |
//                          //Qt::ItemIsDropEnabled |
//                          Qt::ItemIsUserCheckable |
//                          Qt::ItemIsEnabled |
//                          Qt::ItemIsTristate);

    mainListWidget = new SymbolListWidget;

    //左侧树状窗体
    createLeftWidget();


    createData();
    mailListTableConstrucer();
//    mainListWidget->addItems(QStringList() << "1" << "2");

    mainsplit = new QSplitter(Qt::Horizontal,this);
//    mainsplit->addWidget(mailTreeWidget );
//    mainsplit->addWidget(mainListWidget);
    mainsplit->addWidget(leftToolBox);
    mainsplit->addWidget(rightSpliter );
    //设置为主区域窗体
    setCentralWidget(mainsplit );

    mailListTable->installEventFilter(this);
    mailTextEdit->installEventFilter(this);
//    mailTreeWidget->installEventFilter(this);
    mainListWidget->installEventFilter(this);




    /*********************dockwindow用法*********************/

//    //设置主窗口为button
//    QPushButton *btn = new QPushButton("click me",this);
//    btn->setCheckable(true);
//    btn->setChecked(true);
//    setCentralWidget(btn);
//    //设置QDockWidget,标题，允许停靠区域，不可以关闭，拖动等。
//    m_dockwidget = new QDockWidget("docktitle",this,Qt::SubWindow);
//    m_dockwidget->setAllowedAreas(Qt::RightDockWidgetArea  | Qt::LeftDockWidgetArea);
//    m_dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

//    //QTreeWidget
//    QTreeWidget *treewidget = new QTreeWidget;
//    treewidget->insertTopLevelItem(0,new QTreeWidgetItem(treewidget,QStringList()<<"one") );

//    //设置dockWdiget中的Widget为
//    m_dockwidget->setWidget(treewidget);

//    //主窗口增加DockWdiget
//    addDockWidget(Qt::RightDockWidgetArea,m_dockwidget,Qt::Horizontal);

//    //设置窗口显示情况。按钮点击后触发显示与否。
//    connect(btn,SIGNAL(clicked(bool)),m_dockwidget,SLOT(setVisible(bool)) );




          /*********************QStackLayout用法*********************/


    //QMainWindow必须先设置CentralWidget，在CentralWidget上设置layout
//    QWidget *centralwdiget = new QWidget;
//    setCentralWidget(centralwdiget );

//    QListWidget * listWidget = new QListWidget;
//    listWidget->setWindowTitle("ListWidget");
//    listWidget->addItems(QStringList()<<"one" << "two" << "three");

//    QStackedWidget *stack = new QStackedWidget;
//    QTextEdit *edit1 = new QTextEdit("one1");
//    edit1->setWindowTitle("one");
//    QPushButton *edit2 = new QPushButton("one2");
//    edit2->setWindowTitle("two");
//    QTextEdit *edit3 = new QTextEdit("one3");
//    edit3->setWindowTitle("three");
//    stack->addWidget(edit1);
//    stack->addWidget(edit2);
//    stack->addWidget(edit3);

//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(listWidget,1);
//    layout->addWidget(stack,3);

//    centralwdiget->setLayout(layout);

//    connect(listWidget,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)) );
//    listWidget->setCurrentRow(1);

}

Widget::~Widget()
{
}

bool Widget::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyevent = static_cast<QKeyEvent *>(event);
        if(keyevent->key() == Qt::Key_F1 )
        {
            QMessageBox::information(0,"home","home");
            return true;
        }
        else if(keyevent->key() == Qt::Key_Space)
        {
            QMessageBox::information(0,"Key_Space","Key_Space");
        }
    }
    return QMainWindow::event(event);

}

//个人理解：当前窗口A收到此事件后，根据安装事件过滤（安装到B上），B先进行处理，B处理后把此事件发给A继续处理，
//如果A未处理，则A把事件发给父窗口，直到顶层窗口，此事件结束。

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if(object == mailTextEdit || object == mailListTable || object == mailListTable /*mailTreeWidget*/)
    {
        if(event->type() == QEvent::KeyPress )
        {
            QKeyEvent *keyevent =  static_cast<QKeyEvent *>(event);
            if(keyevent->key() == Qt::Key_F1)
            {
                QMessageBox::information(0,"eventFilter","eventFilter");
                //return true; //注释测试顶层窗口和自窗口的事件传递。
            }
        }

    }

    return QMainWindow::eventFilter(object,event);

}

void Widget::dragEnterEvent(QDragEnterEvent *dragEnterEvent)
{
    if(dragEnterEvent->mimeData()->hasFormat("text/uri-list"))
        dragEnterEvent->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *event)
{
    QList<QUrl> url = event->mimeData()->urls();
    if(url.isEmpty())
        return;
    QString filename = url.first().toLocalFile();
    if(readfile(filename))
        setWindowTitle(QString("%1-%2").arg(filename).arg(tr("dragfile")) );
}

bool Widget::readfile(const QString &filename)
{
    qDebug() << filename << "begin" << endl;
    QFile *file = new QFile(filename);
    if(!file->open(QIODevice::ReadOnly))
        return false;
    QTextStream in( file);
    in.setCodec("UTF-8");
    QString text;
    if(!in.atEnd())
    {
        text = in.readAll();
    }
    mailTextEdit->setText(text);
    return true;
}

void Widget::createLeftWidget()
{
    leftToolBox = new QToolBox(this);

    QPushButton *btn1 = new QPushButton("TeamLeaderDialog");
    btn1->setIcon(QIcon(QPixmap(":/resource/0.png")));
    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(TeamLeaderDialog()) );

    QPushButton *btn2 = new QPushButton("SettingViewer");
    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(onSettingViwer()) );
    btn2->setIcon(QIcon(QPixmap(":/resource/1.png")));

    QPushButton *btn3 = new QPushButton("DirectoryViewer");
    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(onDirectoryViewer()) );
    btn2->setIcon(QIcon(QPixmap(":/resource/2.png")));

    leftToolBox->addItem(btn1,"TeamLeaderDialog");
    leftToolBox->addItem(btn2,"reverse");
    leftToolBox->addItem(btn3,"DirectoryViewer");
    leftToolBox->addItem(mainListWidget,"ListWidget");
}

void Widget::createData()
{
    m_SymbolMap.clear();
    m_SymbolMap.insert(0,QString("user0"));
    m_SymbolMap.insert(1,QString("user1"));
    m_SymbolMap.insert(2,QString("user2"));
    m_SymbolMap.insert(3,QString("user3"));
    m_SymbolMap.insert(4,QString("user4"));

}

void Widget::mailListTableConstrucer()
{
    mainListWidget->setEditTriggers(QAbstractItemView::DoubleClicked );
    connect(mainListWidget,SIGNAL(currentTextChanged(QString)), mailTextEdit,SLOT(setText(QString)) );
    mainListWidget->setIconSize(QSize(60,60));
    mainListWidget->setResizeMode(QListView::Adjust);
    QMapIterator<int,QString> i(m_SymbolMap );
    while(i.hasNext())
    {
        i.next();
//        qDebug() << "key= " <<i.key() << "value= " << i.value();
        QListWidgetItem *item = new QListWidgetItem(i.value(),mainListWidget );
        item->setData(Qt::UserRole,i.key() );
        item->setIcon(IconForSymbol(i.key()));
        item->setFlags(item->flags() | Qt::ItemIsEditable );

    }

}

QIcon Widget::IconForSymbol(int id)
{
    return QIcon( QString(":/resource/%1.png").arg(id));
}

void Widget::TeamLeaderDialog()
{
    TeamLeaderDlg dlg;
    dlg.exec();
}

void Widget::onSettingViwer()
{
    SettingViewerDlg dlg;
    dlg.exec();
}

void Widget::onDirectoryViewer()
{
    DirectoryViewer dlg;
    dlg.exec();
}



Ticker::Ticker(QWidget *parent,Qt::WindowFlags flag): QLabel(parent)
{
    myTimerId = 0;  //未启动定时器
    offset = 0;
}

/*AAAAAAAA文字向右侧滚动，滚动到头后，在从左侧开始，跑马灯的效果*/
//void Ticker::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    int textwidth = fontMetrics().width(text()) ;
//    if(textwidth < 1 )
//        return;
//    int x = offset;
//    painter.drawText(x,0,textwidth, height(),Qt::AlignLeft | Qt::AlignVCenter,text() );
//}

/*AAAAAAAA文字向右侧滚动，滚动到头后，在从左侧开始，跑马灯的效果*/
//void Ticker::timerEvent(QTimerEvent *event)
//{
//    if( event->timerId() == myTimerId )
//    {
//        ++offset;
//        if(offset >= width() )
//            offset = -fontMetrics().width(text()) ;
//        scroll(1,0);  //只是用于触发paintEvent事件，本身参数无用，因为在paintEvent中重新进行了实现绘制文本。
//    }
//    else
//    {
//        QLabel::timerEvent(event);
//    }
//}

/*BBBBBBBBBB文字向左侧滚动，滚动到头后，在从左侧开始，跑马灯的效果*/
void Ticker::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int textwidth = fontMetrics().width(text()) ;
    if(textwidth < 1 )
        return;
    int x = offset;
    painter.drawText(x,0,textwidth, height(),Qt::AlignLeft | Qt::AlignVCenter,text() );

    return QWidget::paintEvent(event);
}


/*BBBBBBBBBB文字向左侧滚动，滚动到头后，在从左侧开始，跑马灯的效果*/
void Ticker::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == myTimerId )
    {
        --offset;
        if( offset < -fontMetrics().width(text()) )
            offset = width();

        scroll(-1,0);  //只是用于触发paintEvent事件，本身参数无用，因为在paintEvent中重新进行了实现绘制文本。
    }
    else
    {
        QLabel::timerEvent(event);
    }
}


void Ticker::showEvent(QShowEvent *)
{
    myTimerId = startTimer(30);
}

void Ticker::hideEvent(QHideEvent *)  //在最小化时会发出触发此事件
{
    killTimer( myTimerId );
    myTimerId = 0;
}

TeamLeaderDlg::TeamLeaderDlg(QWidget *parent):
    QDialog(parent)
{
    pview = new QListView(this);
    insertBtn = new QPushButton("insert");
    deletBtn = new QPushButton("delete");
    okBtn = new QPushButton("Ok");
    cancelBtn = new QPushButton("Cancel");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(insertBtn );
    btnLayout->addWidget(deletBtn );
    btnLayout->addWidget(okBtn );
    btnLayout->addWidget(cancelBtn );

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(pview);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addLayout(viewLayout);
    mainlayout->addLayout(btnLayout);

    setLayout(mainlayout);

    pModel = new QStringListModel;
//    pModel->setHeaderData(0,Qt::Horizontal,"one");
    pModel->setStringList(QStringList()<< "one" << "two" );

    pview->setModel(pModel);
    pview->setEditTriggers(QListView::DoubleClicked | QListView::AnyKeyPressed );

    connect(insertBtn,SIGNAL(clicked(bool)),this,SLOT(insert()) );
    connect(deletBtn,SIGNAL(clicked(bool)),this,SLOT(del()) );
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(accept()) );
    connect(okBtn,SIGNAL(clicked(bool)),this,SLOT(reject()) );

}

TeamLeaderDlg::~TeamLeaderDlg()
{

}

void TeamLeaderDlg::insert()
{
    int row;
    QModelIndex index;
    if(pview->currentIndex().isValid())
    {
        row = pview->currentIndex().row();
    }
    else
        row = 0;  //无当前index时，即第一行。

    pModel->insertRows(row,1);
    index = pModel->index(row);
    //    pModel->setData(index,Qt::green,Qt::BackgroundColorRole);  //只对DisplayRole起作用
    pModel->setData(index,"unknown",Qt::DisplayRole);
    pview->setCurrentIndex(index);
    pview->edit(index);






//    index.setdata(Qt::DisplayRole

}

void TeamLeaderDlg::del()
{
    pModel->removeRows(pview->currentIndex().row(),1);
}

SymbolListWidget::SymbolListWidget(QWidget *parent)
    :QListWidget(parent)
{
    setAcceptDrops(true);
}

SymbolListWidget::~SymbolListWidget()
{

}

void SymbolListWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton )
        startPos = event->pos();
    QListWidget::mousePressEvent(event);

}

void SymbolListWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton )  //为什么要使用buttons函数。
    {
        int distance = (e->pos() -startPos ).manhattanLength();
        if(distance >= QApplication::startDragDistance())
            performDrag();

    }

    QListWidget::mouseMoveEvent(e);

}

void SymbolListWidget::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug() << __FUNCTION__ << endl;
//    SymbolListWidget *source = qobject_cast<SymbolListWidget *>(e->source() );
//    if(source && source!=this)
//    {
        QMessageBox::information(0,"1","1");
        e->setDropAction(Qt::MoveAction);
        e->accept();
//    }
}

void SymbolListWidget::performDrag()
{

//    QMessageBox::information(0,"Drag","Drag");
    QListWidgetItem *item = this->currentItem();
    if(item == NULL)
        return;
    QMimeData *mimedata = new QMimeData;
    mimedata->setText(item->text());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimedata);
    drag->setPixmap(QString(":/resource/%1.png").arg(item->data(Qt::UserRole).toInt())  );

    if(drag->exec(Qt::MoveAction) == Qt::MoveAction )
        delete item;

}

MailTableWidget::MailTableWidget(QWidget *parent)
    :QTableWidget(parent)
{
//    setAcceptDrops(true);
}

MailTableWidget::MailTableWidget(int rows, int columns, QWidget *parent)
    :QTableWidget( rows,  columns, parent)
{
    setAcceptDrops(true);
}

MailTableWidget::~MailTableWidget()
{

}

void MailTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << __FUNCTION__ << endl;
//    SymbolListWidget *source = qobject_cast<SymbolListWidget *>(event->source() );
//    if(source && source!=this)
//    {
        qDebug() << "22222"<< endl ;
        event->setDropAction(Qt::MoveAction);
        event->accept();
//    }

}

void MailTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << __FUNCTION__ << endl;
//    MailTableWidget *source = qobject_cast<MailTableWidget *>(event->source() );
//    if(source && source!=this)
//    {
        qDebug() << "33333" << endl;
        event->setDropAction(Qt::MoveAction);
        event->accept();
//    }
}

void MailTableWidget::dropEvent(QDropEvent *event)
{
    qDebug() << __FUNCTION__ << endl;
//    MailTableWidget *source = qobject_cast<MailTableWidget *>(event->source() );
//    if(source && source!=this)
//    {
        qDebug() << "44444" << endl;


        //首先，在构造时，初始化所有的item，然后使用坐标位置找到此item，然后在更新其值
//        QTableWidgetItem *item = currentItem(); //需要点击下此item才能更新其值。
//        QTableWidgetItem *item = itemAt( event->pos() ); //根据鼠标位置更新其值。
//        if(item == NULL)
//             return;
        //在构造时，未初始化所有的item。
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(event->mimeData()->text() );

        QModelIndex index = indexAt(event->pos());
        setItem(index.row(),index.column(),item );

//        event->setDropAction(Qt::MoveAction);
//        event->accept();
        event->acceptProposedAction();

//    }

}

SettingViewer::SettingViewer(QWidget *parent)
{

}

SettingViewer::~SettingViewer()
{

}

SettingViewerDlg::SettingViewerDlg(QWidget *parent)
{

    pTreeWidget = new SettingViewer(this);
    pTreeWidget->setColumnCount(2);
    pTreeWidget->setHeaderLabels(QStringList()<< "item" << "value");

    pTreeWidget->header()->setResizeMode(0,QHeaderView::Stretch );
    pTreeWidget->header()->setResizeMode(1,QHeaderView::Stretch );

    pTreeWidget->insertTopLevelItem(0,new QTreeWidgetItem(QStringList() << "1" << "2") );

    addBtn = new QPushButton("Add");
    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(onAddBtn()) );
    deletBtn = new QPushButton("Delete");
    connect(deletBtn,SIGNAL(clicked(bool)),this,SLOT(ondeletBtn()) );

    QHBoxLayout *Btnlayout = new QHBoxLayout;
    Btnlayout->addWidget(addBtn);
    Btnlayout->addWidget(deletBtn);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pTreeWidget );
    layout->addLayout(Btnlayout);

    setLayout(layout);

    setWindowTitle("SettingViewer");

}

SettingViewerDlg::~SettingViewerDlg()
{

}

void SettingViewerDlg::onAddBtn()
{
    QTreeWidgetItem *pChild = new QTreeWidgetItem;
    pChild->setText(0,"child");
    pChild->setText(1,"valueChild");
    QTreeWidgetItem *curItem = pTreeWidget->currentItem();
    if(curItem == NULL)
    {
        curItem = pTreeWidget->invisibleRootItem();
    }

    curItem->addChild(pChild);

}


void SettingViewerDlg::ondeletBtn()
{
    QTreeWidgetItem *curItem = pTreeWidget->currentItem();
    if(curItem == NULL)
    {
        return;
    }

    QTreeWidgetItem *parentItem = curItem->parent();
    if(parentItem == NULL)
        parentItem = pTreeWidget->invisibleRootItem();

    parentItem->removeChild(curItem);

}

DirectoryViewer::DirectoryViewer(QWidget *parent , Qt::WindowFlags f)
    :QDialog(parent,f)
{
    model = new QDirModel;
    view = new QTreeView(this);
    CreatedirectoryBtn = new QPushButton("Create Directory");
    RemoveBtn = new QPushButton("Remove");
    QuitBtn = new QPushButton("Quit");

    QHBoxLayout  *hboxlayout= new QHBoxLayout;
    hboxlayout->addWidget(CreatedirectoryBtn);
    hboxlayout->addWidget(RemoveBtn);
    hboxlayout->addStretch();
    hboxlayout->addWidget(QuitBtn);

    QVBoxLayout  *Vboxlayout= new QVBoxLayout;
    Vboxlayout->addWidget(view);
    Vboxlayout->addLayout(hboxlayout);

    setLayout(Vboxlayout);

    connect(CreatedirectoryBtn,SIGNAL(clicked(bool)),this,SLOT(onCreate()) );
    connect(RemoveBtn,SIGNAL(clicked(bool)),this,SLOT(onRemove()) );
    connect(QuitBtn,SIGNAL(clicked(bool)),this,SLOT(close()) );

//    model->setReadOnly(false);
    model->setSorting(QDir::Time /*| QDir::DirsFirst | QDir::Name | QDir::IgnoreCase*/);
    view->setModel(model);
    view->header()->setStretchLastSection(true);
    view->header()->setSortIndicator(3,Qt::AscendingOrder);
    view->header()->setSortIndicatorShown(true);
    view->header()->setClickable(true);

    QModelIndex index = model->index(QDir::currentPath());
    view->expand(index);
    view->scrollTo(index);
    view->resizeColumnToContents(0);

}

DirectoryViewer::~DirectoryViewer()
{

}

void DirectoryViewer::onCreate()
{
    QModelIndex index = view->currentIndex();
    if(!index.isValid() )
        return;
    QString dirname = QInputDialog::getText(this,
                                            "Creat Directory",
                                            "Directory Name");
    qDebug() << "dirnmae = " << dirname;

    if(dirname.isEmpty())
        return;

    if(!(model->mkdir(index,dirname).isValid()))
        QMessageBox::information(0,"warning",QString::number(errno) );

}

void DirectoryViewer::onRemove()
{

}
