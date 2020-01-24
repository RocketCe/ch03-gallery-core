#include "picturedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "picture.h"

PictureDao::PictureDao(QSqlDatabase &database):
    mDatabase(database)
{

}

void PictureDao::init() const
{
    if(!mDatabase.tables().contains("pictures")){
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "album_id INTEGER,"
                           "url TEXT;"));
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    Q_UNUSED(albumId)
    QSqlQuery query(mDatabase);
    query.exec(QString("INSERT INTO pictures VALUES ("+QString::number(picture.id())+","+QString::number(picture.albumId())+","+picture.fileUrl().toString()+")"));
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.exec("DELETE FROM pictures WHERE id = "+QString::number(id));
}

void PictureDao::removePictureForAlum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.exec("DELETE FROM pictures WHERE album_id = "+QString::number(albumId));
}

QVector<Picture *> PictureDao::picturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM pictures WHERE album_id = "+QString::number(albumId));
    QVector<Picture *> list;
    while (query.next()) {
        Picture *temp=new Picture;
        temp->setId(query.value("id").toInt());
        temp->setAlbumId(query.value("album_id").toUInt());
        temp->setFileUrl(query.value("url").toString());
        list.push_back(temp);
    }
    return list;
}
