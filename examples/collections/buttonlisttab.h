#ifndef BUTTONLISTTAB_H
#define BUTTONLISTTAB_H

#include <QFrame>


class ButtonListTab : public QFrame
{
    Q_OBJECT
public:
    explicit ButtonListTab(QWidget *parent = 0);
    ~ButtonListTab();

    void initData();
    void initUI();
    void initConnect();

signals:

public slots:

private:
    QStringList m_buttons;
};

#endif // BUTTONLISTTAB_H
