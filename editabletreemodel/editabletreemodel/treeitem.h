#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include <QList>

class TreeItem
{
public:
    TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);//data为列的数据。
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int column); //?
    bool insertColumns(int position, int colunms);
    TreeItem *parent();
    bool removeChildren(int positon, int count, int column);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QList<TreeItem *> childItems;
    QVector<QVariant> itemData;  //保存此Item的每列的数据。
    TreeItem *parentItem;
};

#endif // TREEITEM_H
