#ifndef DBASELINE_H
#define DBASELINE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "libdui_global.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DBaseLine : public QLabel
{
    Q_OBJECT
public:
    explicit DBaseLine(QWidget *parent = 0);

    void setLeftContent(QWidget *content);
    void setRightContent(QWidget *content);

    void setLeftMargin(int margin);
    void setRightMargin(int margin);
    int leftMargin() const;
    int rightMargin() const;

private:
    QHBoxLayout *m_mainLayout = NULL;
    QHBoxLayout *m_leftLayout= NULL;
    QHBoxLayout *m_rightLayout = NULL;

    int m_leftMargin = DUI::HEADER_LEFT_MARGIN;
    int m_rightMargin = DUI::HEADER_RIGHT_MARGIN;
};

DUI_END_NAMESPACE

#endif // DBASELINE_H
