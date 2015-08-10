#ifndef DSWITCHBUTTON_H
#define DSWITCHBUTTON_H

#include <QFrame>
#include <QPixmap>
#include <QVariantAnimation>
#include <QUrl>
#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DSwitchButton : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(double animationStartValue READ animationStartValue WRITE setAnimationStartValue)
    Q_PROPERTY(double animationEndValue READ animationEndValue WRITE setAnimationEndValue)
    Q_PROPERTY(QEasingCurve::Type animationType READ animationType WRITE setAnimationType)
    Q_PROPERTY(QString disabledImageSource READ disabledImageSource WRITE setDisabledImageSource)
    Q_PROPERTY(QString enabledImageSource READ enabledImageSource WRITE setEnabledImageSource)

public:
    explicit DSwitchButton(QWidget *parent = 0);

    bool checked() const;

    int animationDuration() const;

    QEasingCurve::Type animationType() const;
    QString backgroundImageSource() const;

    double animationStartValue() const;
    double animationEndValue() const;
    QString disabledImageSource() const;
    QString enabledImageSource() const;

public Q_SLOTS:
    void setChecked(bool arg);
    void setAnimationDuration(int arg);
    void setAnimationType(QEasingCurve::Type arg);

    void setAnimationStartValue(double animationStartValue);
    void setAnimationEndValue(double animationEndValue);
    bool setDisabledImageSource(const QString &arg);
    bool setEnabledImageSource(const QString &arg);

Q_SIGNALS:
    void checkedChanged(bool arg);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *);
private:
    bool m_checked;

    QPixmap m_enabledImage;
    QPixmap m_disabledImage;
    QVariantAnimation *m_innerAnimation;

    double m_animationStartValue;
    double m_animationEndValue;
    QString m_disabledImageSource;
    QString m_enabledImageSource;
};

DUI_END_NAMESPACE
#endif // DSWITCHBUTTON_H

