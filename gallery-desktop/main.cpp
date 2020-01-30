#include "mainwindow.h"
#include "albumlistwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlbumListWidget w;
    w.show();
    return a.exec();
}
