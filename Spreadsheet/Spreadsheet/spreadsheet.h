#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

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

signals:
    void modified();
public slots:

    void somethingChanged();


private:
    enum {MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26};
    
};

#endif // SPREADSHEET_H
