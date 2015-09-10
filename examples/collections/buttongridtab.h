#ifndef BUTTONGRIDTAB_H
#define BUTTONGRIDTAB_H

#include <QFrame>

class ButtonGridTab : public QFrame
{
    Q_OBJECT
public:
    explicit ButtonGridTab(QWidget *parent = 0);
    ~ButtonGridTab();
    void initData();
    void initUI();
    void initConnect();
signals:

public slots:
    void handleClicked(QString label);
    void handleEnterEvent(QString label);
    void handleLeaveEvent(QString label);
private:
    QStringList m_buttons;
};

#endif // BUTTONGRIDTAB_H
