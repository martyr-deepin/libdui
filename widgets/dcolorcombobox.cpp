#include "dcolorcombobox.h"

DUI_BEGIN_NAMESPACE

class ColorDelegateItem : public QLabel
{
    Q_OBJECT

public:
    explicit ColorDelegateItem(QWidget *parent = 0);
    void setData(const QString &color, const QString &title);

protected:
    void paintEvent(QPaintEvent *);

private:
    QColor m_color;

    const int COLOR_BLOCK_WIDTH = 25;
    const int COLOR_BLOCK_HEIGHT = 10;
};

class DComboBoxColorDelegate : public DAbstractComboBoxDelegate
{
public:
    explicit DComboBoxColorDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

ColorDelegateItem::ColorDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void ColorDelegateItem::setData(const QString &color, const QString &title)
{
    m_color.setNamedColor(color);

    setText(title);

    update();
}

void ColorDelegateItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect colorRect(DUI::MENU_ITEM_LEFT_MARGIN, (DUI::MENU_ITEM_HEIGHT - 10) / 2,
                    COLOR_BLOCK_WIDTH, COLOR_BLOCK_HEIGHT);
    QBrush b(m_color);
    painter.fillRect(colorRect, b);    //draw header color

    QRect textRect(colorRect.x() + colorRect.width() + DUI::TEXT_LEFT_MARGIN, 0, width(), height());

    painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text());  //draw title
}

DComboBoxColorDelegate::DComboBoxColorDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
{

}

QWidget * DComboBoxColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

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

    setModel(new DComboBoxModel(this));

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DColorComboBox::addData(const QColor &color, const QString &title)
{
    QJsonObject colorObj;
    colorObj.insert("itemTitle", QJsonValue(title));
    colorObj.insert("itemColor", color.name(QColor::HexArgb));

    model()->append(colorObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(model()->getModelIndex(model()->count() - 1));
}

void DColorComboBox::addData(const QString &color, const QString &title)
{
    QJsonObject colorObj;
    colorObj.insert("itemTitle", QJsonValue(title));
    colorObj.insert("itemColor", color);

    model()->append(colorObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(model()->getModelIndex(model()->count() - 1));
}

void DColorComboBox::onCurrentIndexChange(int index)
{
    QJsonObject colorObj = model()->getJsonData(index);

    emit currentColorChange(QColor(colorObj["itemColor"].toString()));
}

DUI_END_NAMESPACE

#include "dcolorcombobox.moc"
