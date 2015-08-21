#include "dswitchbutton.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DSwitchButton::DSwitchButton(QWidget *parent) :
    QFrame(parent),
    m_checked(false),
    m_innerAnimation(new QVariantAnimation(this)),
    m_animationStartValue(0),
    m_animationEndValue(0)
{
    setObjectName("DSwitchButton");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    D_THEME_INIT_WIDGET(DSwitchButton);

    connect(m_innerAnimation, &QVariantAnimation::valueChanged, [&](){
        this->update();
    });
}

bool DSwitchButton::checked() const
{
    return m_checked;
}

int DSwitchButton::animationDuration() const
{
    return m_innerAnimation->duration();
}

QEasingCurve::Type DSwitchButton::animationType() const
{
    return m_innerAnimation->easingCurve().type();
}

double DSwitchButton::animationStartValue() const
{
    return m_animationStartValue;
}

double DSwitchButton::animationEndValue() const
{
    return m_animationEndValue;
}

QString DSwitchButton::disabledImageSource() const
{
    return m_disabledImageSource;
}

QString DSwitchButton::enabledImageSource() const
{
    return m_enabledImageSource;
}

void DSwitchButton::setChecked(bool arg)
{
    if (m_checked != arg) {
        m_checked = arg;

        if(arg){
            m_innerAnimation->setStartValue(m_animationStartValue);
            m_innerAnimation->setEndValue(m_animationEndValue);
        }else{
            m_innerAnimation->setStartValue(m_animationEndValue);
            m_innerAnimation->setEndValue(m_animationStartValue);
        }
        m_innerAnimation->start();

        emit checkedChanged(arg);
    }
}

void DSwitchButton::setAnimationDuration(int arg)
{
    m_innerAnimation->setDuration(arg);
}

void DSwitchButton::setAnimationType(QEasingCurve::Type arg)
{
    m_innerAnimation->setEasingCurve(arg);
}

bool DSwitchButton::setDisabledImageSource(const QString &arg)
{
    m_disabledImageSource = arg;

    if(m_disabledImage.load(arg)){
        m_disabledImage = m_disabledImage.scaled(width(), height()*1.2,
                                                Qt::KeepAspectRatioByExpanding,
                                                Qt::SmoothTransformation);

        return true;
    }

    return false;
}

bool DSwitchButton::setEnabledImageSource(const QString &arg)
{
    m_enabledImageSource = arg;

    if(m_enabledImage.load(arg)){
        m_enabledImage = m_enabledImage.scaled(width(), height()*1.2,
                                                Qt::KeepAspectRatioByExpanding,
                                                Qt::SmoothTransformation);

        return true;
    }

    return false;
}

void DSwitchButton::setAnimationStartValue(double animationStartValue)
{
    m_animationStartValue = animationStartValue;
}

void DSwitchButton::setAnimationEndValue(double animationEndValue)
{
    m_animationEndValue = animationEndValue;
}

void DSwitchButton::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);

    QPixmap *m_innerImage;

    if(isEnabled()){
        m_innerImage = &m_enabledImage;
    }else{
        m_innerImage = &m_disabledImage;
    }

    if(m_innerImage->isNull())
        return;

    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), m_innerImage->height()/2.3, m_innerImage->height()/2.3);
    path.closeSubpath();

    p.setClipPath(path);

    double m_innerImageX = 0;

    if(m_innerAnimation->state() == QVariantAnimation::Stopped){
        if(!m_checked){
            m_innerImageX = m_animationStartValue;
        }
    }else{
        m_innerImageX = m_innerAnimation->currentValue().toDouble();
    }

    p.drawPixmap(m_innerImageX,
                 height()/2.0-m_innerImage->height()/2.0,
                 *m_innerImage);

    p.setPen(QPen(QColor("#aa000000"), 2));
    p.drawPath(path);
}

void DSwitchButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        setChecked(!m_checked);
        e->accept();
    }
}

DUI_END_NAMESPACE
