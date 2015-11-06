#ifndef DBOXWIDGET_H
#define DBOXWIDGET_H

#include <QFrame>
#include <QBoxLayout>

#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DBoxWidgetPrivate;
class DBoxWidget : public QFrame, public DObject
{
    Q_OBJECT

    Q_PROPERTY(QBoxLayout::Direction direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    explicit DBoxWidget(QBoxLayout::Direction direction, QWidget *parent = 0);

    QBoxLayout::Direction direction() const;
    QBoxLayout *layout() const;

    void addWidget(QWidget *widget);

public slots:
    void setDirection(QBoxLayout::Direction direction);

signals:
    void sizeChanged(QSize size);
    void directionChanged(QBoxLayout::Direction direction);

protected:
    virtual void updateSize(const QSize &size);
    bool event(QEvent *ee) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DBoxWidget)
};

class DHBoxWidget : public DBoxWidget
{
    Q_OBJECT
public:
    explicit DHBoxWidget(QWidget *parent = 0);
};

class DVBoxWidget : public DBoxWidget
{
    Q_OBJECT
public:
    explicit DVBoxWidget(QWidget *parent = 0);
};

DUI_END_NAMESPACE

#endif // DBOXWIDGET_H
