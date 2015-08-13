#include "dabstractcomboboxdelegate.h"

DAbstractComboBoxDelegate::DAbstractComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void DAbstractComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    //TODO, need to find anther way to get current index
    DUI::DComboBox *cb = static_cast<DUI::DComboBox *>(this->parent());
    if (cb){
        QModelIndex currentIndex = index.model()->index(cb->currentIndex(),0,QModelIndex());
        if (index == currentIndex){
            QPixmap pixmap(cb->normalTickImg());//TODO need hover state
            QRect rect = option.rect;
            rect.setX(DUI::TEXT_LEFT_MARGIN);
            rect.setY(rect.y() + (rect.height() - pixmap.height()) / 2);//draw in vertical center
            rect.setSize(pixmap.size());
            painter->drawPixmap(rect, pixmap);
        }
    }
}

void DAbstractComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
