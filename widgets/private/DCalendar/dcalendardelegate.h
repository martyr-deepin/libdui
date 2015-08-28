#ifndef DCALENDARDELEGATE_H
#define DCALENDARDELEGATE_H

#include <QColor>
#include <QItemDelegate>

class DCalendarDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DCalendarDelegate(QWidget *parent = 0);

    void setBackgroundColor(const QColor & color) {m_backgroundColor = color;}
    QColor getBackgroundColor() const {return m_backgroundColor;}
    void setBackgroundCircleColor(const QColor & color) {m_backgroundCircleColor = color;}
    QColor getBackgroundCircleColor() const {return m_backgroundCircleColor;}
    void setDefaultTextColor(const QColor & color) {m_defaultTextColor = color;}
    QColor getDefaultTextColor() const {return m_defaultTextColor;}
    void setWeekendsTextColor(const QColor & color) {m_weekendsTextColor = color;}
    QColor getWeekendsTextColor() const {return m_weekendsTextColor;}
    void setSelectedTextColor(const QColor & color) {m_selectedTextColor = color;}
    QColor getSelectedTextColor() const {return m_selectedTextColor;}
    void setFestivalTextColor(const QColor & color) {m_festivalTextColor = color;}
    QColor getFestivalTextColor() const {return m_festivalTextColor;}
    void setDefaultLunarColor(const QColor & color) {m_defaultLunarColor = color;}
    QColor getDefaultLunarColor() const {return m_defaultLunarColor;}
    void setWeekendsLunarColor(const QColor & color) {m_weekendsLunarColor = color;}
    QColor getWeekendsLunarColor() const {return m_weekendsLunarColor;}
    void setSelectedLunarColor(const QColor & color) {m_selectedLunarColor = color;}
    QColor getSelectedLunarColor() const {return m_selectedLunarColor;}
    void setFestivalLunarColor(const QColor & color) {m_festivalLunarColor = color;}
    QColor getFestivalLunarColor() const {return m_festivalLunarColor;}

public slots:

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

    QColor m_backgroundColor = Qt::white;
    QColor m_backgroundCircleColor = QColor(33, 147, 202);

    QColor m_defaultTextColor = Qt::black;
    QColor m_weekendsTextColor = Qt::gray;
    QColor m_selectedTextColor = Qt::white;
    QColor m_festivalTextColor = Qt::cyan;
    QColor m_notCurrentTextColor = QColor(0x55, 0x55, 0x55);

    QColor m_defaultLunarColor = Qt::black;
    QColor m_weekendsLunarColor = Qt::gray;
    QColor m_selectedLunarColor = Qt::white;
    QColor m_festivalLunarColor = Qt::cyan;
    QColor m_notCurrentLunarColor = QColor(0x55, 0x55, 0x55);
};

#endif // DCALENDARDELEGATE_H
