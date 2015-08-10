#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>

#include "bartab.h"
#include "buttontab.h"
#include "inputtab.h"
#include "linetab.h"
#include "slidertab.h"
#include "indicatortab.h"
#include "widgetstab.h"
#include "comboboxtab.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initTabWidget();

private:
    QTabWidget * m_mainTab = NULL;
};

#endif // MAINWINDOW_H
