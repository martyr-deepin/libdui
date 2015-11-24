#ifndef DDIALOG_H
#define DDIALOG_H

#include "dabstractdialog.h"

class QPushButton;
class QButtonGroup;
class QLabel;
class QCloseEvent;
class QVBoxLayout;

DUI_BEGIN_NAMESPACE

class DDialogPrivate;
class DDialog : public DAbstractDialog
{
    Q_OBJECT

public:
    explicit DDialog(QWidget *parent = 0);

    void initUI(const QString& icon,
                const QString& message,
                const QString& tipMessage,
                const QStringList& buttonKeys,
                const QStringList& buttonTexts);
    void initConnect();

    QString getIcon() const;
    QString getMessage() const;
    QString getTipMessage() const;
    QStringList getButtons() const;
    QStringList getButtonTexts() const;
    QButtonGroup* getButtonsGroup() const;
    QVBoxLayout* getMessageLayout() const;

signals:
    void aboutToClose();
    void closed();
    void buttonClicked(QString key);
    void buttonClicked(int index);

public slots:
   void setIcon(const QString& icon);
   void setMessage(const QString& message);
   void setTipMessage(const QString& tipMessage);
   void setButtons(const QStringList& buttons);
   void setButtonTexts(const QStringList& buttonTexts);
   void handleButtonsClicked(int id);
   void handleKeyEnter();

protected:
   void closeEvent(QCloseEvent* event);
   void resizeEvent(QResizeEvent* event);

private:
   D_DECLARE_PRIVATE(DDialog)
};

DUI_END_NAMESPACE

#endif // DDIALOG_H
