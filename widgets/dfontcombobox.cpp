#include "dfontcombobox.h"

DUI_USE_NAMESPACE

FontDelegateItem::FontDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void FontDelegateItem::setItemFont(const QString &family, const QString &title)
{
    m_fontFamily = family;
    m_fontTitle = title.isEmpty() ? family : title;
    repaint();
}

void FontDelegateItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(DUI::MENU_ITEM_LEFT_MARGIN, 0, width(), height());

    QFont f;
    f.setFamily(m_fontFamily);
    f.setPixelSize(m_fontPixelSize);
    painter.setFont(f);
    QPen p(m_fontNormalColor);
    painter.setPen(p);

    painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, m_fontTitle);
}
int FontDelegateItem::fontPixelSize() const
{
    return m_fontPixelSize;
}

void FontDelegateItem::setFontPixelSize(int fontPixelSize)
{
    m_fontPixelSize = fontPixelSize;
}

QColor FontDelegateItem::fontNormalColor() const
{
    return m_fontNormalColor;
}

void FontDelegateItem::setFontNormalColor(const QColor &fontNormalColor)
{
    m_fontNormalColor = fontNormalColor;
}

DComboBoxFontDelegate::DComboBoxFontDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
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
    QString title = "";
    QString family = "";
    if (fontItem && dataObj.contains("itemTitle"))
        title = dataObj.value("itemTitle").toString();
    if (fontItem && dataObj.contains("itemFontFamily"))
        family = dataObj.value("itemFontFamily").toString();

    fontItem->setItemFont(family, title);

}

DFontComboBox::DFontComboBox(QWidget *parent) : DComboBox(parent)
{
    DComboBoxFontDelegate *dbfb = new DComboBoxFontDelegate(this);
    setItemDelegate(dbfb);

    m_fontModel = new DComboBoxModel(this);
    setModel(m_fontModel);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DFontComboBox::addFontItem(const QString &family, const QString &title)
{
    QJsonObject nameObj;
    nameObj.insert("itemFontFamily", QJsonValue(family));
    nameObj.insert("itemTitle", QJsonValue(title));

    m_fontModel->append(nameObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(m_fontModel->getModelIndex(m_fontModel->count() - 1));
}

void DFontComboBox::onCurrentIndexChange(int index)
{
    QJsonObject nameObj = m_fontModel->getJsonData(index);

    emit currentFontNameChange(nameObj["itemFont"].toString());
}

