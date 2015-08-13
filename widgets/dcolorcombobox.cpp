#include "dcolorcombobox.h"

DUI_USE_NAMESPACE

ColorDelegateItem::ColorDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void ColorDelegateItem::setData(const QString &color, const QString &title)
{
    m_color.setNamedColor(color);
    m_title = title;

    repaint();
}

void ColorDelegateItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect colorRect(DUI::MENU_ITEM_LEFT_MARGIN, (DUI::MENU_ITEM_HEIGHT - 10) / 2, COLOR_BLOCK_WIDTH, COLOR_BLOCK_HEIGHT);
    QBrush b(m_color);
    painter.fillRect(colorRect, b);    //draw header color

    QRect textRect(colorRect.x() + colorRect.width() + DUI::TEXT_LEFT_MARGIN, 0, width(), height());
    QFont f;
    f.setPixelSize(m_fontPixelSize);
    painter.setFont(f);
    QPen p(m_fontNormalColor);
    painter.setPen(p);
    painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, m_title);  //draw title
}
int ColorDelegateItem::fontPixelSize() const
{
    return m_fontPixelSize;
}

void ColorDelegateItem::setFontPixelSize(int fontPixelSize)
{
    m_fontPixelSize = fontPixelSize;
}

QColor ColorDelegateItem::fontNormalColor() const
{
    return m_fontNormalColor;
}

void ColorDelegateItem::setFontNormalColor(const QColor &fontNormalColor)
{
    m_fontNormalColor = fontNormalColor;
}



DComboBoxColorDelegate::DComboBoxColorDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
{

}

QWidget * DComboBoxColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    ColorDelegateItem * editor = new ColorDelegateItem(parent);
    editor->setFixedHeight(DUI::MENU_ITEM_HEIGHT);

    return editor;
}

void DComboBoxColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QJsonObject dataObj = index.model()->data(index, Qt::DisplayRole).toJsonValue().toObject();

    if (dataObj.isEmpty())
        return;

    ColorDelegateItem *colorItem = static_cast<ColorDelegateItem*>(editor);
    QString color = "#FFFFFFFF";
    QString title = "";
    if (dataObj.contains("itemTitle"))
        title = dataObj.value("itemTitle").toString();
    if (dataObj.contains("itemColor"))
        color = dataObj.value("itemColor").toString();

    if (colorItem)
        colorItem->setData(color, title);
}

DColorComboBox::DColorComboBox(QWidget *parent) : DComboBox(parent)
{
    DComboBoxColorDelegate *d = new DComboBoxColorDelegate(this);
    setItemDelegate(d);

    m_colorModel = new DComboBoxModel(this);
    setModel(m_colorModel);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DColorComboBox::addData(const QColor &color, const QString &title)
{
    QJsonObject colorObj;
    colorObj.insert("itemTitle", QJsonValue(title));
    colorObj.insert("itemColor", color.name(QColor::HexArgb));

    m_colorModel->append(colorObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(m_colorModel->getModelIndex(m_colorModel->count() - 1));
}

void DColorComboBox::addData(const QString &color, const QString &title)
{
    QJsonObject colorObj;
    colorObj.insert("itemTitle", QJsonValue(title));
    colorObj.insert("itemColor", color);

    m_colorModel->append(colorObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(m_colorModel->getModelIndex(m_colorModel->count() - 1));
}

void DColorComboBox::onCurrentIndexChange(int index)
{
    QJsonObject colorObj = m_colorModel->getJsonData(index);

    emit currentColorChange(QColor(colorObj["itemColor"].toString()));
}

