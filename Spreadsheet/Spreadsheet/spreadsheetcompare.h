#ifndef SPREADSHEETCOMPARE_H
#define SPREADSHEETCOMPARE_H
#include <QStringList>

class SpreadsheetCompare
{
public:
    SpreadsheetCompare();

    bool operator()(const QStringList &row1,
                    const QStringList &row2) const;
    enum {KeyCount =3};
    int keys[KeyCount];
    bool ascending[KeyCount];
};

#endif // SPREADSHEETCOMPARE_H
