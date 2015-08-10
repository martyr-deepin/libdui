#ifndef SLIDERTAB_H
#define SLIDERTAB_H

#include <QWidget>
#include <QLabel>

class SliderTab : public QLabel
{
    Q_OBJECT
public:
    explicit SliderTab(QWidget *parent = 0);
};

#endif // SLIDERTAB_H
