#include "picturewidget.h"
#include "ui_picturewidget.h"

PictureWidget::PictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureWidget)
{
    ui->setupUi(this);
}

PictureWidget::~PictureWidget()
{
    delete ui;
}

void PictureWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePicturePixmap();
}

void PictureWidget::updatePicturePixmap()
{
    if(mPixmap.isNull()){
        return;
    }
    ui->pictureLabel->setPixmap(mPixmap.scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio));
}

