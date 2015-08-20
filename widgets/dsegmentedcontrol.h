#ifndef DSEGMENTEDCONTROL_H
#define DSEGMENTEDCONTROL_H

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QList>
#include <QEasingCurve>
#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DSegmentedHighlight : public QToolButton
{
    Q_OBJECT

public:
    explicit DSegmentedHighlight(QWidget *parent = 0);
};

class DSegmentedControl : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationType READ animationType WRITE setAnimationType)
public:
    explicit DSegmentedControl(QWidget *parent = 0);

    int count() const;
    const DSegmentedHighlight *highlight() const;
    int currentIndex() const;
    QToolButton *at(int index) const;
    QString getText(int index) const;
    QIcon getIcon(int index) const;
    int animationDuration() const;
    int indexByTitle(const QString &title) const;

    QEasingCurve::Type animationType() const;

public Q_SLOTS:
    int addSegmented(const QString &title);
    int addSegmented(const QIcon &icon, const QString &title);
    void addSegmented(const QStringList &titleList);
    void addSegmented(const QList<QIcon> &iconList, const QStringList &titleList);
    void insertSegmented(int index, const QString &title);
    void insertSegmented(int index, const QIcon &icon, const QString &title);
    bool setCurrentIndex(int currentIndex);
    bool setCurrentIndexByTitle(const QString &title);
    void setText(int index, const QString &title);
    void setIcon(int index, const QIcon &icon);
    void setAnimationDuration(int animationDuration);
    void setAnimationType(QEasingCurve::Type animationType);

private:
    DSegmentedHighlight *m_highlight;
    QHBoxLayout *m_hLayout;
    QPropertyAnimation *m_highlightMoveAnimation;
    int m_currentIndex;
    QList<QToolButton*> m_tabList;

protected:
    bool eventFilter(QObject *, QEvent *);

private Q_SLOTS:
    void updateHighlightGeometry(bool animation = true);
    void buttonClicked();

Q_SIGNALS:
    void currentChanged(int index);
    void currentTitleChanged(QString title);
    void animationDurationChanged(int animationDuration);
};

DUI_END_NAMESPACE
#endif // DSEGMENTEDCONTROL_H
