#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QJsonDocument>

#include "private/dcombobox_p.h"
#include "dcombobox.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DComboBoxPrivate::DComboBoxPrivate(DComboBox *parent) :
    DObjectPrivate(parent)
{

}

void DComboBoxPrivate::init()
{
    D_Q(DComboBox);

    initInsideFrame();

    //TODO, just work on ediable
    q->setMaxVisibleItems(MAX_VISIBLE_ITEMS);

    //default view not support ::item sub-control
    q->setView(new QListView());

    q->view()->setObjectName("DComboBoxItemView");
    q->view()->setAutoScroll(true);

    maskLabel = new QLabel(q);
    maskLabel->setAttribute(Qt::WA_TranslucentBackground);
    maskLabel->setObjectName("DComboBoxTitleMask");

    q->connect(q, SIGNAL(currentIndexChanged(int)), q, SLOT(_q_slotCurrentIndexChange(int)));
}

//Bypassing the problem here
//qss can't draw box-shadow
void DComboBoxPrivate::initInsideFrame()
{
    D_Q(DComboBox);

    QFrame *insideFrame = new QFrame(q);

    insideFrame->raise();
    insideFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    insideFrame->setObjectName("DComboxInsideFrame");
    //the sub-widget of QCombobox can't Inherits the style sheet from QCombobox
    //so, read the QCombobox's style sheet and set to it sub-widget
    insideFrame->setStyleSheet(q->styleSheet());

    QHBoxLayout *insideLayout = new QHBoxLayout(q);

    insideLayout->setContentsMargins(OUTSIDE_BORDER_WIDTH, OUTSIDE_BORDER_WIDTH,
                                     OUTSIDE_BORDER_WIDTH, OUTSIDE_BORDER_WIDTH);
    insideLayout->addWidget(insideFrame);
}

void DComboBoxPrivate::_q_slotCurrentIndexChange(int index)
{
    D_Q(DComboBox);

    if(q->isEditable()) {
        if(q->currentText().isEmpty()) {
            DComboBoxModel *m = static_cast<DComboBoxModel *>(q->model());

            q->lineEdit()->setText(m->getJsonData(index)["itemText"].toString());
        } else {
            q->lineEdit()->setText(q->currentText());
        }
    } else {
        DComboBoxModel *m = static_cast<DComboBoxModel *>(q->model());
        QWidget *w = q->view()->indexWidget(m->getModelIndex(index));

        if (w)
            maskLabel->setPixmap(w->grab());
    }
}

DComboBox::DComboBox(QWidget *parent) :
    QComboBox(parent),
    DObject(*new DComboBoxPrivate(this))
{
    D_THEME_INIT_WIDGET(DComboBox, alert);

    d_func()->init();
}

void DComboBox::setFixedSize(int w, int h)
{
    D_D(DComboBox);

    QComboBox::setFixedSize(w, h);

    d->maskLabel->setFixedSize(size());
    d->maskLabel->move(-DUI::MENU_ITEM_LEFT_MARGIN + DUI::HEADER_LEFT_MARGIN, 0);
}

void DComboBox::setFixedSize(QSize size)
{
    D_D(DComboBox);

    QComboBox::setFixedSize(size);

    d->maskLabel->setFixedSize(size);
    d->maskLabel->move(-DUI::MENU_ITEM_LEFT_MARGIN + DUI::HEADER_LEFT_MARGIN, 0);
}

QString DComboBox::insensitiveTickImg() const
{
    D_DC(DComboBox);

    return d->insensitiveTickImg;
}

bool DComboBox::isAlert() const
{
    D_DC(DComboBox);

    return d->alert;
}

void DComboBox::setInsensitiveTickImg(const QString &insensitiveTickImg)
{
    D_D(DComboBox);

    d->insensitiveTickImg = insensitiveTickImg;
}

void DComboBox::setAlert(bool alert)
{
    D_D(DComboBox);

    if (d->alert == alert)
        return;

    d->alert = alert;
    emit alertChanged(alert);
}

void DComboBox::setEditable(bool editable)
{
    QComboBox::setEditable(editable);

    view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if(lineEdit())
        lineEdit()->setStyleSheet(styleSheet());
}

QString DComboBox::hoverTickImg() const
{
    D_DC(DComboBox);

    return d->hoverTickImg;
}

void DComboBox::setHoverTickImg(const QString &hoverTickImg)
{
    D_D(DComboBox);

    d->hoverTickImg = hoverTickImg;
}

QString DComboBox::normalTickImg() const
{
    D_DC(DComboBox);

    return d->normalTickImg;
}

void DComboBox::setNormalTickImg(const QString &normalTickImg)
{
    D_D(DComboBox);

    d->normalTickImg = normalTickImg;
}

DComboBox::DComboBox(DComboBoxPrivate &dd, QWidget *parent) :
    QComboBox(parent),
    DObject(dd)
{
    D_THEME_INIT_WIDGET(DComboBox, alert);

    d_func()->init();
}

DUI_END_NAMESPACE

#include "moc_dcombobox.cpp"
