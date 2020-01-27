#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include<memory>
#include<QVector>
#include<QAbstractListModel>

#include"gallery-core_global.h"
#include"picture.h"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORE_EXPORT PictureModel:public QAbstractListModel
{
    Q_OBJECT
public:

    enum PictureRole{FilePathRole=Qt::UserRole+1};

    PictureModel(const AlbumModel& albumModel,QObject* parent=nullptr);


private:
    DatabaseManager& mDb;
    int mAlbumId;

};

#endif // PICTUREMODEL_H
