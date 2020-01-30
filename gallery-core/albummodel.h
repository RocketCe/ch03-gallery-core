#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include<QAbstractListModel>
#include<QHash>
#include<vector>
#include<memory>

#include"gallery-core_global.h"
#include"album.h"
#include"databasemanager.h"


class GALLERYCORE_EXPORT AlbumModel:public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles{IdRole=Qt::UserRole+1,NameRole};

    explicit AlbumModel(QObject * parent=nullptr);

    QModelIndex addAlbum(const Album &album);

    int rowCount(const QModelIndex &parent= QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index,const QVariant &value,int role) override;
    bool removeRows(int row,int count,const QModelIndex &parent) override;

    QHash<int,QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex &index) const;

    DatabaseManager &mDb;
    std::vector<std::unique_ptr<Album>> mAlbums;
};

#endif // ALBUMMODEL_H
