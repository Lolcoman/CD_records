#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QItemDelegate>

class ImageDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ImageDelegate(QObject *parent = nullptr);
protected:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // IMAGEDELEGATE_H
