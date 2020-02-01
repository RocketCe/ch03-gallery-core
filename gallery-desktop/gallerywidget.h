#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>
#include<QItemSelectionModel>
#include"albummodel.h"
#include"picturemodel.h"
#include"thumbnailproxymodel.h"

namespace Ui {
class GalleryWidget;
}

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryWidget(QWidget *parent = nullptr);
    ~GalleryWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel *selectModel);
    void setPictureModel(ThumbnailProxyModel * thumbnailProxyModel);
    void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

signals:
    void pictureActivated(const QModelIndex& index);


private:
    Ui::GalleryWidget *ui;
};

#endif // GALLERYWIDGET_H
