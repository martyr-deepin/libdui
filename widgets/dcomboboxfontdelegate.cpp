#include "dcomboboxfontdelegate.h"

DUI_USE_NAMESPACE

FontDelegateItem::FontDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void FontDelegateItem::setItemFont(const QString &fontName)
{
    m_fontName = fontName;
    repaint();
}
QColor FontDelegateItem::fontColor() const
{
    return m_fontColor;
}

void FontDelegateItem::setFontColor(const QColor &fontColor)
{
    m_fontColor = fontColor;
}

void FontDelegateItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(DUI::MENU_ITEM_LEFT_MARGIN, 0, width(), height());

    QFont f(m_fontName, m_fontPointSize);
    painter.setFont(f);
    QPen p(m_fontColor);
    painter.setPen(p);

    painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, m_fontName);
}

int FontDelegateItem::fontPointSize() const
{
    return m_fontPointSize;
}

void FontDelegateItem::setFontPointSize(int fontPixelSize)
{
    m_fontPointSize = fontPixelSize;
}



DComboBoxFontDelegate::DComboBoxFontDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget * DComboBoxFontDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    FontDelegateItem * editor = new FontDelegateItem(parent);
    editor->setFixedHeight(DUI::MENU_ITEM_HEIGHT);

    return editor;
}

void DComboBoxFontDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QJsonObject dataObj = index.model()->data(index, Qt::DisplayRole).toJsonValue().toObject();

    if (dataObj.isEmpty())
        return;

    FontDelegateItem *fontItem = static_cast<FontDelegateItem*>(editor);
    if (fontItem && dataObj.contains("itemFont"))
        fontItem->setItemFont(dataObj.value("itemFont").toString());
}

void DComboBoxFontDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

