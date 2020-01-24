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

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.exec(QString("DELETE FROM pictures WHERE album_id = ") + QString::number(id));
    query.exec(QString("DELETE FROM albums WHERE id = ") + QString::number(id));
}

QVector<Album *> AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums",mDatabase);
    query.exec();
    QVector<Album*> list;
    while (query.next()) {
        Album* album=new Album;
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list.append(album);
    }
    return list;
}

