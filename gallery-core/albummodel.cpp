#include "albummodel.h"


AlbumModel::AlbumModel(QObject *parent):
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbums(mDb.albumDao.albums())
{

}

QModelIndex AlbumModel::addAlbum(const Album &album)
{
    int rowIndex=rowCount();
    beginInsertRows(QModelIndex(),rowIndex,rowIndex);
    std::unique_ptr<Album> newAlbum(new Album(album));
    mDb.albumDao.addAlbum(*newAlbum);
    mAlbums.push_back(std::move(newAlbum));
    endInsertRows();
    return index(rowIndex,0);
}

int AlbumModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);


    return mAlbums.size();
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
    if(!isIndexValid(index)){
        return  QVariant();
    }
    const Album& album=*mAlbums.at(index.row());

    switch (role) {
    case Roles::IdRole:
        return album.id();
    case Roles::NameRole:
        return album.name();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[Roles::IdRole]="id";
    roles[Roles::NameRole]="name";
    return roles;
}
