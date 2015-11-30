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

public:
    DAbstractDialog(QWidget *parent = 0);

public slots:
    void moveToCenter();
    void moveToTopRight();
    void moveToCenterByRect(const QRect &rect);
    void moveToTopRightByRect(const QRect &rect);

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
