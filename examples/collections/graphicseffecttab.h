#ifndef GRAPHICSEFFECTTAB_H
#define GRAPHICSEFFECTTAB_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "dgraphicsgloweffect.h"

DUI_USE_NAMESPACE

class GraphicsEffectTab : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsEffectTab(QWidget *parent = 0);
    ~GraphicsEffectTab();

};

#endif // GRAPHICSEFFECTTAB_H
