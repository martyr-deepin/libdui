#include "dsimplecombobox.h"

DUI_USE_NAMESPACE


SimpleDelegateItem::SimpleDelegateItem(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void SimpleDelegateItem::setText(const QString &text)
{
    m_text = text;

    repaint();
}

void SimpleDelegateItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(DUI::MENU_ITEM_LEFT_MARGIN, 0, width(), height());

    QFont f;
    f.setPixelSize(m_fontPixelSize);
    painter.setFont(f);
    QPen p(m_fontNormalColor);
    painter.setPen(p);

    painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, m_text);
}
int SimpleDelegateItem::fontPixelSize() const
{
    return m_fontPixelSize;
}

void SimpleDelegateItem::setFontPixelSize(int fontPixelSize)
{
    m_fontPixelSize = fontPixelSize;
}

QColor SimpleDelegateItem::fontNormalColor() const
{
    return m_fontNormalColor;
}

void SimpleDelegateItem::setFontNormalColor(const QColor &fontNormalColor)
{
    m_fontNormalColor = fontNormalColor;
}



DComboBoxSimpleDelegate::DComboBoxSimpleDelegate(QObject *parent) : DAbstractComboBoxDelegate(parent)
{

}

QWidget * DComboBoxSimpleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
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

    m_simpleModel = new DComboBoxModel(this);
    setModel(m_simpleModel);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChange(int)));
}

void DSimpleComboBox::addItem(const QString &text)
{
    QJsonObject nameObj;
    nameObj.insert("itemText", QJsonValue(text));

    m_simpleModel->append(nameObj);
    // Make the combo boxes always displayed.
    view()->openPersistentEditor(m_simpleModel->getModelIndex(m_simpleModel->count() - 1));
}

void DSimpleComboBox::addItems(const QStringList &texts)
{
    foreach (QString text, texts) {
        this->addItem(text);
    }
}

void DSimpleComboBox::onCurrentIndexChange(int index)
{
    QJsonObject nameObj = m_simpleModel->getJsonData(index);

    emit currentTextChanged(nameObj["itemText"].toString());
}


