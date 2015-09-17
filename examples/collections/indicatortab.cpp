#include "indicatortab.h"

IndicatorTab::IndicatorTab(QWidget *parent) :
    QLabel(parent)
{
    setStyleSheet("IndicatorTab{background-color: #252627;}");

    //////////////////////////////////////////////////////////////--DLoadingIndicator
    ///
    QLabel *loadingContainer = new QLabel(this);
    QVBoxLayout * loadingContainerLayout = new QVBoxLayout(loadingContainer);
    loadingContainer->setLayout(loadingContainerLayout);
    loadingContainer->setFixedSize(200, 200);

    DLoadingIndicator *loadingIndicator = new DLoadingIndicator(":/images/test.png", this);
    loadingIndicator->setLoading(true);
    loadingIndicator->setAniDuration(2000);
    loadingIndicator->setAniEasingCurve(QEasingCurve::OutInCubic);
    QColor color("gray");
    loadingIndicator->setBackgroundColor(color);

    DLoadingIndicator *loadingIndicator2 = new DLoadingIndicator(this);
    loadingIndicator2->setLoadingPixmap(QPixmap(":/images/test.png"));
    loadingIndicator2->setLoading(true);

    loadingContainerLayout->addWidget(loadingIndicator);
    loadingContainerLayout->addWidget(loadingIndicator2);
}