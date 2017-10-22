#include "treeitem.h"


TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    this->itemData = data;
    this->parentItem = parent;
    this->childItems.clear();
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number) //�����ض���child��
{
    return childItems.value(number);
}

int TreeItem::childCount() const
{
    return childItems.size();
    //return childItems->count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

bool TreeItem::insertChildren(int position, int count, int column)
{
    //countΪ�ڵ�ǰλ��Ҫ���뼸�����ӡ�columnΪitem����������
    //positionΪ����ĺ��������к����е�λ�á�
    if(position < 0 || position > childItems.size())
        return false;
    for(int row = 0; row < count; ++row)
    {
        QVector<QVariant> colnumnData(column); //����һ���洢�����ݵı�����
        TreeItem *newItem = new TreeItem(colnumnData, this);
        childItems.insert(position, newItem);
    }

    return true;
}

bool TreeItem::insertColumns(int position, int colunms)
{
    //ʾ������ÿ�ж���ӣ�Ӧ�����ڸ��ڵ���ô˺�����
    if(position < 0 || position > itemData.size())
        return false;
    for(int col = 0; col < colunms; ++col)
    {
        itemData.insert(position, QVariant());
    }


    foreach (TreeItem * child, childItems)
    {
        child->insertColumns(position, colunms);
    }

    return true;
}

TreeItem *TreeItem::parent()
{
    return this->parent();
}

bool TreeItem::removeChildren(int positon, int count, int column)
{
    if(positon < 0 || (positon+count) > childItems.size())
        return false;

    for(int row = 0; row < count; ++row)
    {
        delete childItems.takeAt(positon);
    }

    return true;
}

bool TreeItem::removeColumns(int position, int columns)
{

}

int TreeItem::childNumber() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem *>(this));  //const_cast��̫�ǵ�
    return 0;
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if(column <0 || column > itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
