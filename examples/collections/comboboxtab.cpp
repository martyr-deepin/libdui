#include "comboboxtab.h"
#include <QLineEdit>

ComboBoxTab::ComboBoxTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ComboBoxTab{background-color: #252627;}");

    cb = new DComboBox(this);
    cb->setFixedSize(300, DUI::BUTTON_HEIGHT);
    cb->move(100, 200);

    DComboBoxFontDelegate *dbfb = new DComboBoxFontDelegate();
    cb->setItemDelegate(dbfb);

    model = new DComboBoxModel();
    cb->setModel(model);

    for (int i = 0; i < 10; i ++){
        QJsonObject object
        {
            {"itemFont", QString::number(i)}
        };
        model->append(object);
        // Make the combo boxes always displayed.
        cb->view()->openPersistentEditor(model->getModelIndex(model->count() - 1));
    }

    cb->setCurrentIndex(1);
}


