#include "spreadsheet.h"
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include "cell.h"

Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent)
{
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(somethingChanged()));
    clear();
}

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for(int i = 0; i < ColumnCount; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)) );
        setHorizontalHeaderItem(i,item);
        //for(int j = 0; j < RowCount; ++j)

    }

    setCurrentItem(0,0);
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}

void Spreadsheet::cut()
{
    //QMessageBox::information(this,"CUT","TEST");
    copy();
    del();

}

void Spreadsheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = "";
    for(int i = 0; i < range.rowCount(); ++i)
    {
        if(i > 0)
        str += "\n";
        for(int j = 0; j < range.columnCount(); ++j )
        {
            if(j > 0 )
                str +="\t";
        }
    }

    QApplication::clipboard()->setText(str);


}

void Spreadsheet::paste()
{
    QString str = QApplication::clipboard()->text();
    QStringList rowStrList = str.split("\n");
    QStringList columnStrList = "";
    for(int i = 0; i < rowStrList.size(); ++i)
    {
        columnStrList = rowStrList.at(i);
        for(int j = 0; j < columnStrList.size(); ++j)
        {
//
        }
    }
}

void Spreadsheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if(!items.isEmpty())
        foreach(QTableWidgetItem *item, items)
            delete item;
    somethingChanged();
}

QString Spreadsheet::currentLocation() const
{
    return QChar('A'+currentColumn())+ QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const
{

}

QString Spreadsheet::formula(int row, int column) const
{

}

void Spreadsheet::somethingChanged()
{
    emit modified();
}
