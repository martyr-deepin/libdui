#include "dimagebutton.h"
#include "dconstants.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DImageButton::DImageButton(QWidget *parent)
    : QLabel(parent)
{
    D_THEME_INIT_WIDGET(DImageButton);
    changeState();
}

DImageButton::DImageButton(const QString &normalPic, const QString &hoverPic, const QString &pressPic, QWidget *parent)
    : QLabel(parent)
{
    D_THEME_INIT_WIDGET(DImageButton);

    if (!normalPic.isEmpty())
        m_normalPic = QPixmap(normalPic);
    if (!hoverPic.isEmpty())
        m_hoverPic = QPixmap(hoverPic);
    if (!pressPic.isEmpty())
        m_pressPic = QPixmap(pressPic);

    setCheckable(false);

    changeState();
}

DImageButton::DImageButton(const QString &normalPic, const QString &hoverPic,
                           const QString &pressPic, const QString &checkedPic, QWidget *parent)
    : QLabel(parent)
{
    D_THEME_INIT_WIDGET(DImageButton);

    if (!normalPic.isEmpty())
        m_normalPic = QPixmap(normalPic);
    if (!hoverPic.isEmpty())
        m_hoverPic = QPixmap(hoverPic);
    if (!pressPic.isEmpty())
        m_pressPic = QPixmap(pressPic);
    if (!checkedPic.isEmpty())
        m_checkedPic = QPixmap(checkedPic);

    setCheckable(true);

    changeState();
}

DImageButton::~DImageButton()
{
}

void DImageButton::enterEvent(QEvent *event)
{
    if (!m_isChecked){
        m_state = Hover;
        changeState();
    }

    QLabel::enterEvent(event);
}

void DImageButton::leaveEvent(QEvent *event)
{
    if (!m_isChecked){
        m_state = Normal;
        changeState();
    }
    QLabel::leaveEvent(event);
}

void DImageButton::mousePressEvent(QMouseEvent *event)
{
    m_state = Press;
    changeState();

    QLabel::mousePressEvent(event);
}

void DImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_state = Hover;
    changeState();

    emit clicked();

    if (m_isCheckable){
        m_isChecked = !m_isChecked;
        if (m_isChecked){
            m_state = Checked;
        } else {
            m_state = Normal;
        }
        changeState();
    }

    QLabel::mouseReleaseEvent(event);
}

void DImageButton::changeState()
{
    switch (m_state) {
    case Hover:     if (!m_hoverPic.isNull()) setPixmap(m_hoverPic);      break;
    case Press:     if (!m_pressPic.isNull()) setPixmap(m_pressPic);      break;
    case Checked:   if (!m_checkedPic.isNull()) setPixmap(m_checkedPic);   break;
    default:        if (!m_normalPic.isNull()) setPixmap(m_normalPic);    break;
    }

    emit stateChanged();
}

void DImageButton::setCheckable(bool flag)
{
    m_isCheckable = flag;

    if (!m_isCheckable){
        m_state = Normal;
        changeState();
    }
}

void DImageButton::setChecked(bool flag)
{
    if (m_isCheckable == false){
        return;
    }

    m_isChecked = flag;
    if (m_isChecked){
        m_state = Checked;        
    } else {
        m_state = Normal;
    }
    changeState();
}

bool DImageButton::isChecked()
{
    return m_isChecked;
}

bool DImageButton::isCheckable()
{
    return m_isCheckable;
}

void DImageButton::setNormalPic(const QPixmap &normalPicPixmap)
{
    m_normalPic = normalPicPixmap;
    changeState();
}

void DImageButton::setHoverPic(QPixmap &hoverPicPixmap)
{
    m_hoverPic = hoverPicPixmap;
    changeState();
}

void DImageButton::setPressPic(QPixmap &pressPicPixmap)
{
    m_pressPic = pressPicPixmap;
    changeState();
}

void DImageButton::setCheckedPic(QPixmap &checkedPicPixmap)
{
    m_checkedPic = checkedPicPixmap;
    changeState();
}

DUI_END_NAMESPACE
