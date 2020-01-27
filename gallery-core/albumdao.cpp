#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "databasemanager.h"

AlbumDao::AlbumDao(QSqlDatabase &database):
    mDatabase(database)
{

}

void AlbumDao::init() const
{
    if(!mDatabase.tables().contains("albums")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT");
    }
}

void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name",album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.exec("UPDATE albums SET name = '"+album.name()+"' WHERE id = "+QString::number(album.id()));
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.exec(QString("DELETE FROM pictures WHERE album_id = ") + QString::number(id));
    query.exec(QString("DELETE FROM albums WHERE id = ") + QString::number(id));
}

QVector<std::unique_ptr<Album>> AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums",mDatabase);
    query.exec();
    QVector<std::unique_ptr<Album>> list;
    while (query.next()) {
        auto album=std::make_unique<Album>();
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list.append(std::move(album));
    }
    return list;
}

