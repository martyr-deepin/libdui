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
    m_maskLabel->setFixedSize(size());
    m_maskLabel->move(0, 0);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChange(int)));
}

void DComboBox::slotCurrentIndexChange(int index)
{
    DComboBoxModel *m = static_cast<DComboBoxModel *>(model());
    QWidget *w = view()->indexWidget(m->getModelIndex(index));

    if (w)
        m_maskLabel->setPixmap(w->grab());
}



