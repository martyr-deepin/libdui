#include <QFontMetrics>

#include "dfontcombobox.h"

DUI_BEGIN_NAMESPACE

class FontDelegateItem : public QLabel
{
    Q_OBJECT

public:
    explicit FontDelegateItem(QWidget *parent = 0);

    void setItemFont(const QString &family, const QString &title);
};

class DComboBoxFontDelegate : public DAbstractComboBoxDelegate
{
public:
    explicit DComboBoxFontDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

FontDelegateItem::FontDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void FontDelegateItem::setItemFont(const QString &family, const QString &title)
{
    QFont font = this->font();

    font.setFamily(family);

    setFont(font);

    setText(title.isEmpty() ? family : title);
}

DComboBoxFontDelegate::DComboBoxFontDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
{

}

QWidget * DComboBoxFontDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

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

    setModel(new DComboBoxModel(this));

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DFontComboBox::addFontItem(const QString &family, const QString &title)
{
    QJsonObject nameObj;
    nameObj.insert("itemFontFamily", QJsonValue(family));
    nameObj.insert("itemTitle", QJsonValue(title));

    model()->append(nameObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(model()->getModelIndex(model()->count() - 1));
}

void DFontComboBox::onCurrentIndexChange(int index)
{
    QJsonObject nameObj = model()->getJsonData(index);

    emit currentFontNameChange(nameObj["itemFont"].toString());
}

DUI_END_NAMESPACE

#include "dfontcombobox.moc"
