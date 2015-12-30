#include "dsimplecombobox.h"
#include "private/dcombobox_p.h"

DUI_BEGIN_NAMESPACE

class SimpleDelegateItem : public DComboBoxItem
{
    Q_OBJECT

public:
    explicit SimpleDelegateItem(QWidget *parent = 0);
};

class DComboBoxSimpleDelegate : public DAbstractComboBoxDelegate
{
public:
    explicit DComboBoxSimpleDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

SimpleDelegateItem::SimpleDelegateItem(QWidget *parent) :
    DComboBoxItem(parent)
{

}

DComboBoxSimpleDelegate::DComboBoxSimpleDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
{

}

QWidget * DComboBoxSimpleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    SimpleDelegateItem * editor = new SimpleDelegateItem(parent);
    editor->setFixedHeight(DUI::MENU_ITEM_HEIGHT);

    return editor;
}

void DComboBoxSimpleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QJsonObject dataObj = index.model()->data(index, Qt::DisplayRole).toJsonValue().toObject();

    if (dataObj.isEmpty())
        return;

    SimpleDelegateItem *simpleItem = static_cast<SimpleDelegateItem *>(editor);
    QString title = "";

    if (simpleItem && dataObj.contains("itemText"))
        title = dataObj.value("itemText").toString();

    simpleItem->setText(title);

}


DSimpleComboBox::DSimpleComboBox(QWidget *parent) : DComboBox(parent)
{

    DComboBoxSimpleDelegate *dbfb = new DComboBoxSimpleDelegate(this);
    setItemDelegate(dbfb);

    setModel(new DComboBoxModel(this));

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DSimpleComboBox::addItem(const QString &text)
{
    QJsonObject nameObj;
    nameObj.insert("itemText", QJsonValue(text));

    dcomboBoxModel()->append(nameObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(dcomboBoxModel()->getModelIndex(dcomboBoxModel()->count() - 1));
}

void DSimpleComboBox::addItems(const QStringList &texts)
{
    foreach (QString text, texts) {
        this->addItem(text);
    }
}

void DSimpleComboBox::onCurrentIndexChange(int index)
{
    QJsonObject nameObj = dcomboBoxModel()->getJsonData(index);

    emit currentTextChanged(nameObj["itemText"].toString());
}

DUI_END_NAMESPACE

#include "dsimplecombobox.moc"
