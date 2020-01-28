#include "picturemodel.h"
#include "databasemanager.h"
#include "albummodel.h"

PictureModel::PictureModel(const AlbumModel &albumModel, QObject *parent):
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mAlbumId(-1),
    mPictures()
{
    connect(&albumModel,&AlbumModel::rowsRemoved,this,&PictureModel::deletePictureForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rowIndex=rowCount();
    beginInsertRows(QModelIndex(),rowIndex,rowIndex);
    std::unique_ptr<Picture> newPicture(new Picture(picture));
    mDb.pictureDao.addPictureInAlbum(mAlbumId,*newPicture);
    mPictures.push_back(std::move(newPicture));
    endInsertRows();
    return index(rowIndex,0);
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return  mPictures.size();
}

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if(!isIndexValid(index)){
        return  QVariant();
    }
    const Picture& picture=*mPictures.at(index.row());

    switch (role) {
    case PictureRole::FilePathRole:
        return picture.fileUrl();
    default:
        return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0 || row>=rowCount() || count<0 || (row+count)>rowCount()){
        return false;
    }
    beginRemoveRows(parent,row,row+count-1);
    int countLeft=count;
    while (countLeft--) {
        const Picture& picture=*mPictures.at(row+countLeft);
        mDb.pictureDao.removePicture(picture.id());
    }
    mPictures.erase(mPictures.begin()+row,mPictures.begin()+row+count);
    endRemoveRows();
    return true;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId=albumId;
    loadPictures(albumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{

}

void PictureModel::loadPictures(int albumId)
{
    if(albumId<=0){
        mPictures.clear();
        return;
    }
    mPictures=mDb.pictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    return index.row()<mPictures.size();
}
