#ifndef IMAGEBUTTONGRIDTAB_H
#define IMAGEBUTTONGRIDTAB_H

#include <QFrame>

class ImageButtonGridTab : public QFrame
{
    Q_OBJECT
public:
    explicit ImageButtonGridTab(QWidget *parent = 0);
    ~ImageButtonGridTab();
    void initData();
    void initUI();
    void initConnect();
signals:

public slots:
    void handleClicked(QString label);
private:
    QList<QMap<QString, QString>> m_imageInfos;
};


#endif // IMAGEBUTTONGRIDTAB_H
