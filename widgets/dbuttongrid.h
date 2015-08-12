#ifndef DBUTTONGRID_H
#define DBUTTONGRID_H

#include <QTableWidget>

#include "libdui_global.h"
#include "dconstants.h"

class QButtonGroup;

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DButtonGrid : public QTableWidget
{
    Q_OBJECT
public:
    explicit DButtonGrid(QWidget *parent = 0);
    explicit DButtonGrid(int rows, int columns, QWidget *parent = 0);
    ~DButtonGrid();

    void init();
    void initConnect();
    void setItemUnChecked();
    void setItemSize(int width, int height);

public slots:
    void addButton(const QString& label, int index);
    void addButtons(const QStringList& listLabels);
    void checkButtonByIndex(int index);

private slots:
    void setButtonChecked(int id);

signals:
    void buttonChecked(QString label);
    void buttonCheckedIndexChanged(int index);

private:
    QButtonGroup* m_buttonGroup = NULL;
    int m_rowHeight = 40;
    int m_columnWidth = 100;
};

DUI_END_NAMESPACE

#endif // DBUTTONGRID_H
