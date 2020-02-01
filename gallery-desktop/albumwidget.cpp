#include "albumwidget.h"
#include "ui_albumwidget.h"

#include<QInputDialog>
#include<QFileDialog>

#include"albummodel.h"
#include"picturemodel.h"
#include"thumbnailproxymodel.h"
#include"picturedelegate.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mAlbumSelectionModel(nullptr),
    mPictureModel(nullptr),
    mPictureSelectionModel(nullptr)
{
    ui->setupUi(this);
    clearUi();

    ui->thumbnailListview->setSpacing(5);
    ui->thumbnailListview->setResizeMode(QListView::Adjust);
    ui->thumbnailListview->setFlow(QListView::LeftToRight);
    ui->thumbnailListview->setWrapping(true);

    ui->thumbnailListview->setItemDelegate(new PictureDelegate(this));

    connect(ui->thumbnailListview,&QListView::doubleClicked,this,&AlbumWidget::pictureActivated);
    connect(ui->deleteButton,&QPushButton::clicked,this,&AlbumWidget::deleteAlbum);
    connect(ui->editButton,&QPushButton::clicked,this,&AlbumWidget::editAlbum);
    connect(ui->addPicturesButton,&QPushButton::clicked,this,&AlbumWidget::addPictures);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel)
{
    mAlbumModel=albumModel;
    connect(mAlbumModel,&QAbstractItemModel::dataChanged,[this](const QModelIndex& topLeft){
        if(topLeft==mAlbumSelectionModel->currentIndex()){
            loadAlbum(topLeft);
        }
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel *albumSelectionModel)
{
    mAlbumSelectionModel=albumSelectionModel;
    connect(mAlbumSelectionModel,&QItemSelectionModel::selectionChanged,[this](const QItemSelection& selected){
        if(selected.isEmpty()){
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first());
    });
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel *pictureModel)
{
    mPictureModel=pictureModel;
    ui->thumbnailListview->setModel(mPictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->thumbnailListview->setSelectionModel(selectionModel);
}

void AlbumWidget::deleteAlbum()
{
    if(mAlbumSelectionModel->selectedIndexes().isEmpty()){
        return;
    }
    int row=mAlbumSelectionModel->currentIndex().row();
    mAlbumModel->removeRow(row);

    QModelIndex previousModeIndex=mAlbumModel->index(row-1,0);

    if(previousModeIndex.isValid()){
        mAlbumSelectionModel->setCurrentIndex(previousModeIndex,QItemSelectionModel::SelectCurrent);
        return;
    }

    QModelIndex nextModelIndex=mAlbumModel->index(row,0);
    if(nextModelIndex.isValid()){
        mAlbumSelectionModel->setCurrentIndex(nextModelIndex,QItemSelectionModel::SelectCurrent);
        return;
    }
}

void AlbumWidget::editAlbum()
{
    if(mAlbumSelectionModel->selectedIndexes().isEmpty()){
        return;
    }
    QModelIndex currentAlbumIndex=mAlbumSelectionModel->selectedIndexes().first();
    QString oldAlbumName=mAlbumModel->data(currentAlbumIndex,AlbumModel::Roles::NameRole).toString();
    bool ok;

    QString newName=QInputDialog::getText(this,"Album's name","Change Album name",QLineEdit::Normal,oldAlbumName,&ok);

    if(ok && !newName.isEmpty()){
        mAlbumModel->setData(currentAlbumIndex,newName,AlbumModel::Roles::NameRole);
    }

}

void AlbumWidget::addPictures()
{
    QStringList filenames=QFileDialog::getOpenFileNames(this,"add pictures",QDir::homePath(),"Picture files(*.jpg *.png)");
    if(!filenames.isEmpty()){
        QModelIndex lastModelIndex;
        for(auto filename:filenames){
            Picture picture(filename);
            lastModelIndex=mPictureModel->pictureModel()->addPicture(picture);
        }
        ui->thumbnailListview->setCurrentIndex(lastModelIndex);
    }
}

void AlbumWidget::clearUi()
{
    ui->albumName->setText("");
    ui->deleteButton->setVisible(false);
    ui->editButton->setVisible(false);
    ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex &albumIndex)
{
    mPictureModel->pictureModel()->setAlbumId(mAlbumModel->data(albumIndex,AlbumModel::Roles::IdRole).toInt());

    ui->albumName->setText(mAlbumModel->data(albumIndex,Qt::DisplayRole).toString());

    ui->deleteButton->setVisible(true);
    ui->editButton->setVisible(true);
    ui->addPicturesButton->setVisible(true);
}
