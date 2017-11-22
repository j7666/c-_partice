#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QString>
#include "cell.h"

class SpreadsheetCompare;
class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit Spreadsheet(QWidget *parent = 0);
    void clear();
    QTableWidgetSelectionRange selectedRange()const;


public:
    void cut();
    void copy();
    void paste();
    void del();
    QString currentLocation() const;
    QString currentFormula() const;
    QString text(int row, int column) const;
    QString formula(int row, int column) const;
    void setFormula(int row , int column, const QString &formula);
    Cell *celled(int row ,int column) const;
    void selectcolumn();
    void selectrow();
    void showGrid(bool flag);
    void AutoRecalculate();
    void sort(const SpreadsheetCompare &compare);


signals:
    void modified();


public slots:

    void somethingChanged();
    void slotFindPrevious(const QString &str,Qt::CaseSensitivity cs);
    void slotFindNext(const QString &str,Qt::CaseSensitivity cs);

    void slotSetAutoRecalc(bool recalc);


private:
    enum {MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26};

    bool bAutoRecacl;

};

#endif // SPREADSHEET_H
