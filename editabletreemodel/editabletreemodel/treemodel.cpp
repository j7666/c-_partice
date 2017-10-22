#include "treemodel.h"

treemodel::treemodel(const QStringList &headers,const QString &data, QObject *parent):
    QAbstractItemModel(parent)
{
    //headers为列名，data参数为需要展示的所有的数据。
    QVector<QVariant> rootData;
    foreach (QString header, headers) {
        rootData << header;
    }

    rootItem = new TreeItem(rootData);//构造Model后，首先把列名传入，可以显示列名。
    setupModelData(data.split(QString("\n")), rootItem);//data为实际的树的数据。
}


treemodel::~treemodel()
{
    delete rootItem;
}

QVariant treemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);
    return QVariant();
}

QVariant treemodel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);
    return item->data(index.column());
}

int treemodel::columnCount(const QModelIndex &) const
{
    return rootItem->columnCount();
}

int treemodel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

QModelIndex treemodel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() && parent.column() != 0)
        return QModelIndex(); //不在第0列

    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row,column,childItem);
    else
        return QModelIndex();
}

QModelIndex treemodel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(child);
    TreeItem *parentitem = childItem->parent();

    if(parentitem == rootItem)
        return QModelIndex();
    return createIndex(parentitem->childNumber(), 0, parentitem);
}

Qt::ItemFlags treemodel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool treemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Qt::EditRole != role)
        return false;

    TreeItem *item = getItem(index);

    bool result = item->setData(index.column(), value);
    if(result)    emit dataChanged(index, index);

    return result;


}

bool treemodel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);
    if(result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

bool treemodel::insertColumns(int column, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, column, column + count -1 );
    success = rootItem->insertColumns(column, count);
    endInsertColumns();

    return success;
}

bool treemodel::insertRows(int row, int count, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;
    beginInsertRows(parent, row, row+count-1);
    success = parentItem->insertChildren(row,count,rootItem->columnCount());
    endInsertRows();

    return success;
}

bool treemodel::removeColumns(int column, int count, const QModelIndex &parent)
{
    bool success;
    beginRemoveColumns(parent, column, column+count-1);
    success = rootItem->removeColumns(column, count);
    endRemoveColumns();

    if(rootItem->columnCount() == 0)
        removeRows(0,rowCount());

    return success;
}

bool treemodel::removeRows(int row, int count, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, row, row+count-1);
    success = parentItem->removeChildren(row, count,rootItem->columnCount());
    endRemoveRows();

    return success;
}

void treemodel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;
    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        number++;
    }
}

TreeItem *treemodel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if(item) return item;
    }
    return rootItem;
}
