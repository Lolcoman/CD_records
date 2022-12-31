#include "imagedelegate.h"
#include <QSpinBox>
#include <QApplication>

//Delegate pro vykreselní obrázku z byteArray z databáze
ImageDelegate::ImageDelegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *ImageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
//Paint provede převod a následné vykreslení obrázku
void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPixmap loadedImage;
    loadedImage.loadFromData(index.data().toByteArray());
    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();
    style->drawItemPixmap(painter,option.rect,Qt::AlignCenter,loadedImage);
}

void ImageDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void ImageDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
}

void ImageDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
