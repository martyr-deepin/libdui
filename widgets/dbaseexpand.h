#ifndef DBASEEXPAND_H
#define DBASEEXPAND_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>

#include "libdui_global.h"
#include "dseparatorhorizontal.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class ContentLoader : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int height READ height WRITE setFixedHeight)
public:
    explicit ContentLoader(QWidget *parent = 0) : QLabel(parent){}
};

class LIBDUISHARED_EXPORT DBaseExpand : public QWidget
{
    Q_OBJECT
public:
    explicit DBaseExpand(QWidget *parent = 0);
    ~DBaseExpand();

    void setHeader(QWidget *header);
    void setContent(QWidget *content);
    inline QWidget *getContent() const {return m_content;}
    void setHeaderHeight(int height);
    virtual void setExpand(bool value);
    void updateContentHeight();
    bool expand() const;
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve curve);
    void setSeparatorVisible(bool arg);
    void setExpandedSeparatorVisible(bool arg);

signals:
    void expandChange(bool e);
    void sizeChanged(QSize s);

private:
    QWidget *m_header = NULL;
    QWidget *m_content = NULL;
    QVBoxLayout *m_headerLayout = NULL;
    QVBoxLayout *m_contentLayout = NULL;
    ContentLoader *m_contentLoader = NULL;
    DSeparatorHorizontal * m_hSeparator = NULL;
    DSeparatorHorizontal *m_bottom_separator = NULL;
    QPropertyAnimation *m_animation = NULL;
    bool m_expand = false;
};

DUI_END_NAMESPACE

#endif // DBASEEXPAND_H
