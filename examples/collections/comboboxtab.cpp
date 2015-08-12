#include "comboboxtab.h"
#include <QLineEdit>

ComboBoxTab::ComboBoxTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ComboBoxTab{background-color: #252627;}");

    ////////////////////////////////////////////////Font ComboBox
    cb = new DComboBox(this);
    cb->setFixedSize(200, DUI::BUTTON_HEIGHT);
    cb->move(30, 100);

    DComboBoxFontDelegate *dbfb = new DComboBoxFontDelegate();
    cb->setItemDelegate(dbfb);

    model = new DComboBoxModel();
    cb->setModel(model);

    for (int i = 0; i < 100; i ++){
        QJsonObject object
        {
            {"itemFont", QString::number(i)}
        };
        model->append(object);
        // Make the combo boxes always displayed.
        cb->view()->openPersistentEditor(model->getModelIndex(model->count() - 1));
    }

    cb->setCurrentIndex(1);

    /////////////////////////////////////////////Color ComboBox
    colorCB = new DComboBox(this);
    colorCB->setFixedSize(200, DUI::BUTTON_HEIGHT);
    colorCB->move(300, 100);

    DComboBoxColorDelegate *colorDelegate = new DComboBoxColorDelegate();
    colorCB->setItemDelegate(colorDelegate);

    colorModel = new DComboBoxModel();
    colorCB->setModel(colorModel);

    for (int i = 0; i < 10; i ++){
        QJsonObject object
        {
            {"itemTitle", QString::number(i)},
            {"itemColor", QString("#%1%2%3%4FF").arg(i).arg(i).arg(i).arg(i)}//support RRGGBB or AARRGGBB or color-name
        };
        colorModel->append(object);
        // Make the combo boxes always displayed.
        colorCB->view()->openPersistentEditor(colorModel->getModelIndex(colorModel->count() - 1));
    }
    connect(colorCB, SIGNAL(currentIndexChanged(int)), this, SLOT(colorIndexChange(int)));
}

void ComboBoxTab::colorIndexChange(int index)
{
    qWarning() << colorModel->getJsonData(index) << "=======";
}


