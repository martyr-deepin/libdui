#include "dcombobox.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DComboBox::DComboBox(QWidget *parent) : QComboBox(parent)
{
    D_THEME_INIT_WIDGET(DComboBox);
    //TODO, just work on ediable
    setMaxVisibleItems(MAX_VISIBLE_ITEMS);

    view()->setObjectName("DComboBoxItemView");
    view()->setAutoScroll(true);

    m_maskLabel = new QLabel(this);
    m_maskLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_maskLabel->setObjectName("DComboBoxTitleMask");

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChange(int)));
}

void DComboBox::setFixedSize(int w, int h)
{
    QComboBox::setFixedSize(w, h);

    m_maskLabel->setFixedSize(size());
    m_maskLabel->move(-DUI::MENU_ITEM_LEFT_MARGIN + DUI::HEADER_LEFT_MARGIN, 0);
}

void DComboBox::setFixedSize(QSize size)
{
    QComboBox::setFixedSize(size);

    m_maskLabel->setFixedSize(size);
    m_maskLabel->move(-DUI::MENU_ITEM_LEFT_MARGIN + DUI::HEADER_LEFT_MARGIN, 0);
}

void DComboBox::slotCurrentIndexChange(int index)
{
    DComboBoxModel *m = static_cast<DComboBoxModel *>(model());
    QWidget *w = view()->indexWidget(m->getModelIndex(index));

    if (w)
        m_maskLabel->setPixmap(w->grab());
}



