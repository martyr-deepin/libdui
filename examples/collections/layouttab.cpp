#include <QPushButton>
#include <QScrollArea>
#include <QLabel>

#include "layouttab.h"
#include "dflowlayout.h"
#include "anchors.h"

LayoutTab::LayoutTab(QWidget *parent) : QWidget(parent)
{
    QWidget *widget = new QWidget;
    DUI::DFlowLayout *m_layout = new DUI::DFlowLayout(widget);

    m_layout->setSpacing(10);
    m_layout->setFlow(QListView::TopToBottom);
    widget->setLayoutDirection(Qt::RightToLeft);

    connect(m_layout, &DUI::DFlowLayout::sizeHintChanged,
            this, [widget, m_layout](const QSize &size) {
        if(m_layout->flow() == DUI::DFlowLayout::Flow::TopToBottom) {
            widget->setFixedWidth(size.width());
        }
    });

    int i = 99;

    auto onButtonClicked = [m_layout, this] {
        QPushButton *button = qobject_cast<QPushButton*>(sender());

        if(!button)
            return;

        if(button->text().toInt() % 2) {
            QLabel *label = new QLabel;

            label->setPixmap(QPixmap(":/images/wallpaper/1.jpg").scaledToWidth(80));

            m_layout->insertWidget(1, label);
        } else {
            QWidget *widget = m_layout->itemAt(1)->widget();

            if(widget) {
                m_layout->removeWidget(widget);
                widget->deleteLater();
            }
        }
    };

    while(i-- > 0) {
        QPushButton *button = new QPushButton(QString::number(i));

        m_layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, onButtonClicked);
    }

    QHBoxLayout *main_layout = new QHBoxLayout(this);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);

    QScrollArea *scroll = new QScrollArea;

    main_layout->addWidget(scroll);

    scroll->setWidget(widget);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidgetResizable(true);
}

