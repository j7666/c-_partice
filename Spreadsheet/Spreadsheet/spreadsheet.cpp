#include "spreadsheet.h"
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>


Spreadsheet::Spreadsheet(QWidget *parent) :
    QTableWidget(parent)
{
    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(somethingChanged()));
    clear();
    bAutoRecacl = false;
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
        {
            str += "\n";
        }

        for(int j = 0; j < range.columnCount(); ++j )
        {
            if(j > 0 )
                str +="\t";
            str += formula( range.topRow() + i, range.leftColumn() + j );
        }
    }
    QApplication::clipboard()->setText(str);


}

void Spreadsheet::paste()
{

    QString str = QApplication::clipboard()->text();
    QMessageBox::information(0,"",str);
    QStringList rowStrList = str.split("\n");
    QString strColumn = "";

    QTableWidgetSelectionRange range = selectedRange();
    int leftColumn =  range.leftColumn();
    int topRow =  range.topRow();

    for(int i = 0; i < rowStrList.size(); ++i)
    {
        strColumn = rowStrList.at(i);
        QStringList strListColumn = strColumn.split("\t");
        for(int j = 0 ; j < strListColumn.size(); j++)
            setFormula(topRow + i, leftColumn + j, strListColumn[j] );
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
    return formula( currentRow(),currentColumn() );
}

QString Spreadsheet::text(int row, int column) const
{
    Cell *c = celled(row, column);
    if(!c)
    {
        return "";
    }
    return c->text();
}

QString Spreadsheet::formula(int row, int column) const
{
    Cell *c = celled(row, column);
    if(!c)
    {
        return "";
    }
    return c->formula();
}

void Spreadsheet::setFormula(int row, int column, const QString &formula)
{
    Cell *c = celled(row, column);
    if(!c)
    {
        c = new Cell;
        setItem(row,column,c);
    }
    c->setFormula(formula);

}

Cell *Spreadsheet::celled(int row, int column) const
{
    return static_cast<Cell *>(item(row, column));
}

void Spreadsheet::selectcolumn()
{
    selectColumn(currentColumn());
}

void Spreadsheet::selectrow()
{
    selectRow(currentRow());
}

void Spreadsheet::showGrid(bool flag)
{

}

void Spreadsheet::AutoRecalculate()
{
    for(int i = 0; i < RowCount; i ++ )
    {
        for(int j = 0; j < ColumnCount; j++ )
        {
            Cell *cell = celled(i , j);
            if(cell)
                cell->setDirty();
        }
    }

    viewport()->update(); //更新显示的数据
}

void Spreadsheet::sort(const SpreadsheetCompare &compare)
{

}

void Spreadsheet::somethingChanged()
{
    if(bAutoRecacl)
        AutoRecalculate();

    emit modified();
}

void Spreadsheet::slotFindPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    //QMessageBox::information(0,"1",str);
    int row = currentRow();
    int column = currentColumn() - 1;
    while(row >= 0)
    {
        while(column >= 0 )
        {
            if(text(row,column).contains(str,cs))
            {
                //clearSelection();
                setCurrentCell(row,column);
                activateWindow();
                return;
            }
            --column;
        }
        column = ColumnCount - 1;
        --row;
    }
    QApplication::beep();

}

void Spreadsheet::slotFindNext(const QString &str, Qt::CaseSensitivity cs)
{
    //QMessageBox::information(0,"2",str);
    int row = currentRow();
    int column = currentColumn() + 1;
    while(row < RowCount)
    {
        while(column < ColumnCount)
        {
            if(text(row,column).contains(str,cs))
            {
                //clearSelection();
                setCurrentCell(row,column);
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }
    QApplication::beep();

}

void Spreadsheet::slotSetAutoRecalc(bool recalc)
{
    bAutoRecacl = recalc;
    if(bAutoRecacl)
        AutoRecalculate();
}
