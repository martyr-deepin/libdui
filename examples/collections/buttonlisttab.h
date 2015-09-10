#ifndef BUTTONLISTTAB_H
#define BUTTONLISTTAB_H

#include <QFrame>
class QListWidgetItem;

class ButtonListTab : public QFrame
{
    Q_OBJECT
public:
    explicit ButtonListTab(QWidget *parent = 0);
    ~ButtonListTab();

    void initData();
    void initUI();
    void initConnect();

public slots:
    void handleEnter(QString text);
    void handleLeave(QString text);
private:
    QStringList m_buttons;
};

#endif // BUTTONLISTTAB_H
