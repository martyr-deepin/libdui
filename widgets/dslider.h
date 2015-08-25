#ifndef DSLIDER_H
#define DSLIDER_H

#include <QSlider>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int handleType READ handleType)
    Q_PROPERTY(QColor tipColor READ tipColor WRITE setTipColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
public:
    enum HandleType {
        SharpHandler,
        RoundHandle
    };

    DSlider(QWidget * parent = 0);
    DSlider(Qt::Orientation orientation, QWidget * parent = 0);
    ~DSlider();

    int handleType() const;
    void setHandleType(HandleType handleType);

    QString leftTip() const;
    void setLeftTip(const QString &leftTip);

    QString rightTip() const;
    void setRightTip(const QString &rightTip);

    QColor tipColor() const;
    void setTipColor(const QColor &tipColor);

    QColor scaleColor() const;
    void setScaleColor(const QColor &scaleColor);

    void addScale(int value);
    void removeScale(int value);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent * event);

private:
    int m_handleType = RoundHandle;

    QString m_leftTip;
    QString m_rightTip;
    QList<int> m_scales;

    QColor m_tipColor = Qt::black;
    QColor m_scaleColor = Qt::black;

    int getScalePosition(int value);
};

DUI_END_NAMESPACE

#endif // DSLIDER_H
