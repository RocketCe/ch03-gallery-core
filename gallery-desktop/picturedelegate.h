#ifndef PICTUREDELEGATE_H
#define PICTUREDELEGATE_H

#include <QStyledItemDelegate>

class PictureDelegate:public QStyledItemDelegate
{
public:
    explicit PictureDelegate(QObject *parent=nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PICTUREDELEGATE_H
