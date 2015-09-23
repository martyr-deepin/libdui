#include "graphicseffecttab.h"

GraphicsEffectTab::GraphicsEffectTab(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QPushButton *glowEffectButton = new QPushButton("GlowEffect");
    glowEffectButton->setFixedWidth(100);
    DGraphicsGlowEffect *effect = new DGraphicsGlowEffect(this);
    effect->setBlurRadius(20.0);
    effect->setDistance(1);
    effect->setYOffset(3);
    glowEffectButton->setGraphicsEffect(effect);

    mainLayout->addWidget(glowEffectButton);
}

GraphicsEffectTab::~GraphicsEffectTab()
{

}

