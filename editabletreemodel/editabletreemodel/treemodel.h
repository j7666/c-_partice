#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "treeitem.h"


class treemodel : public QAbstractItemModel
{
    Q_OBJECT
public:
    treemodel(const QStringList &headers,const QString &data, QObject *parent = 0);
    ~treemodel();
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const ;
    QVariant data(const QModelIndex &index, int role) const;
    int columnCount(const QModelIndex & = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;


    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *rootItem;
signals:
    
public slots:
    
};

#endif // TREEMODEL_H
