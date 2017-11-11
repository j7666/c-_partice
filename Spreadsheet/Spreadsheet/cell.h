#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();
    Cell(int row ,int column);

    QString formula() const;
    void setFormula(const QString &formula);
    QVariant data(int role) const;
    void setData(int role, const QVariant &value);
    void setDirty();

    QTableWidgetItem *clone() const;

private:
    QVariant value() const;
    QVariant evalExpression(const QString &str, int &pos)const ;
    QVariant evalTerm(const QString &str, int &pos) const;
    QVariant evalFactor(const QString &str, int &pos) const;

    mutable QVariant cacheValue;
    mutable bool cacheIsDirty;

};

#endif // CELL_H
