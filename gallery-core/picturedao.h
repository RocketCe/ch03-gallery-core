#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <QVector>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
    explicit PictureDao(QSqlDatabase& database);
    void init() const;

    void addPictureInAlbum(int albumId,Picture &picture) const;
    void removePicture(int id) const;
    void removePictureForAlum(int albumId) const;

    QVector<Picture *> picturesForAlbum(int albumId) const;

private:
    QSqlDatabase & mDatabase;
};

#endif // PICTUREDAO_H
