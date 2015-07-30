#include "dseparatorhorizontal.h"

DUI_BEGIN_NAMESPACE

DSeparatorHorizontal::DSeparatorHorizontal(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(parent->width());
    m_topRec = new QWidget(this);
    m_topRec->setObjectName("DSeparatorTopRec");
    m_bottomRec = new QWidget(this);
    m_bottomRec->setObjectName("DSeparatorBottomRec");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch();
    mainLayout->addWidget(m_topRec);
    mainLayout->addWidget(m_bottomRec);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

DUI_END_NAMESPACE
