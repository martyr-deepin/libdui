#ifndef INDICATORTAB_H
#define INDICATORTAB_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "dloadingindicator.h"

DUI_USE_NAMESPACE

class IndicatorTab : public QLabel
{
    Q_OBJECT
public:
    explicit IndicatorTab(QWidget *parent = 0);
};

#endif // INDICATORTAB_H
