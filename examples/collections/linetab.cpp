#include "linetab.h"

LineTab::LineTab(QWidget *parent) : QWidget(parent)
{
        //////////////////////////////////////////////////////////////--DSeparator
        DSeparatorHorizontal *dsHorizontal = new DSeparatorHorizontal(this);
        dsHorizontal->setFixedSize(200,2);
        dsHorizontal->move(1,5);
        DSeparatorVertical *dsVertical = new DSeparatorVertical(this);
        dsVertical->setFixedSize(2,200);
        dsVertical->move(10,5);

        //////////////////////////////////////////////////////////////--DBaseLine
        DBaseLine * baseLine = new DBaseLine(this);
        baseLine->setFixedSize(400,30);
        baseLine->move(20,30);
        baseLine->setLeftContent(new QLabel("DBaseLine"));
        QPushButton *bbb = new QPushButton("Test button",this);
        bbb->setStyleSheet("background-color: red");
        baseLine->setRightContent(bbb);

        //////////////////////////////////////////////////////////////--DHeaderLine
        DHeaderLine *headerLine = new DHeaderLine(this);
        headerLine->setFixedSize(400, 30);
        headerLine->move(20,70);
        headerLine->setTitle("控件库");
}

