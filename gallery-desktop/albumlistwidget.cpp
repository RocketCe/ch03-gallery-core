#include "albumlistwidget.h"
#include "ui_albumlistwidget.h"

AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget)
{
    ui->setupUi(this);
}

AlbumListWidget::~AlbumListWidget()
{
    delete ui;
}
