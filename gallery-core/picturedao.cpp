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
    QSqlQuery query(mDatabase);
    query.exec(QString("INSERT INTO pictures (album_id,url) VALUES ("+QString::number(albumId)+",'"+picture.fileUrl().toString()+"')"));
    picture.setAlbumId(albumId);
    picture.setId(query.lastInsertId().toInt());
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

std::vector<std::unique_ptr<Picture>> PictureDao::picturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM pictures WHERE album_id = "+QString::number(albumId));
    std::vector<std::unique_ptr<Picture>> list;
    while (query.next()) {
        auto temp=std::make_unique<Picture>();
        temp->setId(query.value("id").toInt());
        temp->setAlbumId(query.value("album_id").toUInt());
        temp->setFileUrl(query.value("url").toString());
        list.push_back(std::move(temp));
    }
    return list;
}
