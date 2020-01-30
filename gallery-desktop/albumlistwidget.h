#ifndef ALBUMLISTWIDGET_H
#define ALBUMLISTWIDGET_H

#include <QWidget>

namespace Ui {
class AlbumListWidget;
}

class AlbumListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListWidget(QWidget *parent = nullptr);
    ~AlbumListWidget();

private:
    Ui::AlbumListWidget *ui;
};

#endif // ALBUMLISTWIDGET_H
