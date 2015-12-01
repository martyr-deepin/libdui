#ifndef DABSTRACTDIALOG_H
#define DABSTRACTDIALOG_H

#include <QDialog>
#include <QPoint>

#include "libdui_global.h"
#include "dobject.h"

class QMouseEvent;
class QPushButton;
class QResizeEvent;

DUI_BEGIN_NAMESPACE

class DAbstractDialogPrivate;
class DAbstractDialog : public QDialog, public DObject
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

public:
    DAbstractDialog(QWidget *parent = 0);

    QColor backgroundColor() const;
    QColor borderColor() const;

public slots:
    void moveToCenter();
    void moveToTopRight();
    void moveToCenterByRect(const QRect &rect);
    void moveToTopRightByRect(const QRect &rect);

    void setBackgroundColor(QColor backgroundColor);
    void setBorderColor(QColor borderColor);

protected:
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

protected:
    DAbstractDialog(DAbstractDialogPrivate &dd, QWidget *parent = 0);

private:
    D_DECLARE_PRIVATE(DAbstractDialog)
};

DUI_END_NAMESPACE

#endif // DABSTRACTDIALOG_H
