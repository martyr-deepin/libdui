#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QScreen>
#include <QPainter>
#include <QWidget>
#include <QDebug>

#include "dabstractdialog.h"
#include "private/dabstractdialogprivate_p.h"

DUI_BEGIN_NAMESPACE

DAbstractDialogPrivate::DAbstractDialogPrivate(DAbstractDialog *qq):
    DObjectPrivate(qq)
{

}

void DAbstractDialogPrivate::init()
{
    D_Q(DAbstractDialog);

    q->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    q->setAttribute(Qt::WA_TranslucentBackground);
}

QRect DAbstractDialogPrivate::getParentGeometry() const
{
    D_QC(DAbstractDialog);

    if (q->parentWidget()) {
        return q->parentWidget()->geometry();
    } else {
        QPoint pos = QCursor::pos();

        for (QScreen *screen : qApp->screens()) {
            if (screen->geometry().contains(pos)) {
                return screen->geometry();
            }
        }
    }

    return qApp->desktop()->geometry();
}

DAbstractDialog::DAbstractDialog(QWidget *parent) :
    QDialog(parent),
    DObject(*new DAbstractDialogPrivate(this))
{
    d_func()->init();
}

void DAbstractDialog::moveToCenter()
{
    D_DC(DAbstractDialog);

    moveToCenterByRect(d->getParentGeometry());
}

void DAbstractDialog::moveToTopRight()
{
    D_DC(DAbstractDialog);

    moveToTopRightByRect(d->getParentGeometry());
}

void DAbstractDialog::moveToTopRightByRect(const QRect &rect)
{
    int x = rect.x() + rect.width() - width();
    move(QPoint(x, 0));
}

void DAbstractDialog::moveToCenterByRect(const QRect &rect)
{
    QRect qr = frameGeometry();
    qr.moveCenter(rect.center());
    move(qr.topLeft());
}

void DAbstractDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        D_D(DAbstractDialog);

        d->dragPosition = event->globalPos() - frameGeometry().topLeft();
    }

    QDialog::mousePressEvent(event);
}

void DAbstractDialog::mouseMoveEvent(QMouseEvent *event)
{
    D_DC(DAbstractDialog);

    move(event->globalPos() - d->dragPosition);

    QDialog::mouseMoveEvent(event);
}

void DAbstractDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(255, 255, 255, 51), 2));
    painter.setBrush(QColor(0, 0 , 0, 204));
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect r(1, 1, width() - 2, height() - 2);
    painter.drawRoundedRect(r, 2, 2, Qt::RelativeSize);

    QDialog::paintEvent(event);
}

DAbstractDialog::DAbstractDialog(DAbstractDialogPrivate &dd, QWidget *parent):
    QDialog(parent),
    DObject(dd)
{
    dd.init();
}

DUI_END_NAMESPACE
