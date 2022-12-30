#include "imagedelegate.h"
#include <QSpinBox>
#include <QApplication>

ImageDelegate::ImageDelegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *ImageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPixmap loadedImage;
    loadedImage.loadFromData(index.data().toByteArray());
    loadedImage.scaled(500,500);
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
