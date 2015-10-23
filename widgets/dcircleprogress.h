#ifndef DCIRCLEPROGRESS_H
#define DCIRCLEPROGRESS_H

#include <QWidget>

class DCircleProgress : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor MEMBER m_chunkColor DESIGNABLE true)
    Q_PROPERTY(QColor chunkColor MEMBER m_backgroundColor DESIGNABLE true)

public:
    explicit DCircleProgress(QWidget *parent = 0);


    int value() const {return m_currentValue;}
    void setValue(int value);
    inline const QString text() const {return m_displayText;}
    inline void setText(const QString &text) {m_displayText = text;}

signals:
    void valueChanged(const int value) const;

private:
    void paintEvent(QPaintEvent *e);

private:
    int m_lineWidth = 3;
    int m_currentValue = 40;
    int m_minmumValue = 0;
    int m_maximumValue = 100;

    QString m_displayText;

    QColor m_chunkColor = Qt::cyan;
    QColor m_backgroundColor = Qt::darkCyan;
};

#endif // DCIRCLEPROGRESS_H
