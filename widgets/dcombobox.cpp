#include "dcombobox.h"
#include "dthememanager.h"
#include "QHBoxLayout"
#include <QFrame>

DUI_USE_NAMESPACE

DComboBox::DComboBox(QWidget *parent) : QComboBox(parent)
{
    D_THEME_INIT_WIDGET(DComboBox);

    initInsideFrame();

    //TODO, just work on ediable
    setMaxVisibleItems(MAX_VISIBLE_ITEMS);

    //default view not support ::item sub-control
    setView(new QListView());
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

//Bypassing the problem here
//qss can't draw box-shadow
void DComboBox::initInsideFrame()
{
    QFrame *insideFrame = new QFrame(this);
    insideFrame->raise();
    insideFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    insideFrame->setObjectName("DComboxInsideFrame");
    //the sub-widget of QCombobox can't Inherits the style sheet from QCombobox
    //so, read the QCombobox's style sheet and set to it sub-widget
    insideFrame->setStyleSheet(this->styleSheet());
    QHBoxLayout *insideLayout = new QHBoxLayout(this);
    insideLayout->setContentsMargins(OUTSIDE_BORDER_WIDTH, OUTSIDE_BORDER_WIDTH, OUTSIDE_BORDER_WIDTH, OUTSIDE_BORDER_WIDTH);
    insideLayout->addWidget(insideFrame);
}

QString DComboBox::insensitiveTickImg() const
{
    return m_insensitiveTickImg;
}

void DComboBox::setInsensitiveTickImg(const QString &insensitiveTickImg)
{
    m_insensitiveTickImg = insensitiveTickImg;
}

QString DComboBox::hoverTickImg() const
{
    return m_hoverTickImg;
}

void DComboBox::setHoverTickImg(const QString &hoverTickImg)
{
    m_hoverTickImg = hoverTickImg;
}

QString DComboBox::normalTickImg() const
{
    return m_normalTickImg;
}

void DComboBox::setNormalTickImg(const QString &normalTickImg)
{
    m_normalTickImg = normalTickImg;
}




