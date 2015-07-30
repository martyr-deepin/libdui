#include "linetab.h"

LineTab::LineTab(QWidget *parent) : QLabel(parent)
{
        setStyleSheet("LineTab{background-color: #252627;}");
        //////////////////////////////////////////////////////////////--DSeparator
        DSeparatorHorizontal *dsHorizontal = new DSeparatorHorizontal(this);
        dsHorizontal->setFixedSize(200,2);
        dsHorizontal->move(1,5);
        DSeparatorVertical *dsVertical = new DSeparatorVertical(this);
        dsVertical->setFixedSize(2,200);
        dsVertical->move(10,5);

        //////////////////////////////////////////////////////////////--DHeaderLine
        DHeaderLine *headerLine = new DHeaderLine(this);
        headerLine->setFixedSize(400, 30);
        headerLine->move(20,30);
        headerLine->setTitle("控件库");

        //////////////////////////////////////////////////////////////--DBaseLine
        DBaseLine * baseLine = new DBaseLine(this);
        baseLine->setFixedSize(400,30);
        baseLine->setLeftContent(new QLabel("DBaseLine"));
        QPushButton *bbb = new QPushButton("Test button",this);
        bbb->setStyleSheet("background-color: red");
        baseLine->setRightContent(bbb);

        //////////////////////////////////////////////////////////////--DBaseExpand
        DBaseExpand *baseExpand = new DBaseExpand(this);
        baseExpand->setFixedWidth(300);
        baseExpand->setHeader(baseLine);
        connect(bbb, &QPushButton::clicked, [=]{
            baseExpand->setExpand(!baseExpand->expand());
        });
        DSeparatorHorizontal *dsHorizontal2 = new DSeparatorHorizontal(this);
        dsHorizontal2->setFixedWidth(baseExpand->width());
        QLabel *expandLabel = new QLabel("Expand content");
        expandLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        expandLabel->setFixedSize(200,50);
        baseExpand->setContent(expandLabel);
        baseExpand->move(20,70);
        dsHorizontal2->move(baseExpand->x(),baseExpand->y() - 2);

        /////////////////////////////////////////////////////////////--DArrowLineExpand
        DArrowLineExpand *arrowLineExpand = new DArrowLineExpand(this);
        arrowLineExpand->setFixedWidth(300);
        arrowLineExpand->setTitle("Arrow Line Expand");
        QLabel *expandLabel2 = new QLabel("Arrow Expand content");
        expandLabel2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        expandLabel2->setFixedSize(200,50);
        arrowLineExpand->setContent(expandLabel2);
        arrowLineExpand->move(350, 70);
}

