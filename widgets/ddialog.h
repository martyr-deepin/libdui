#ifndef DDIALOG_H
#define DDIALOG_H

#include <QIcon>

#include "dabstractdialog.h"

class QAbstractButton;
class QButtonGroup;
class QLabel;
class QCloseEvent;
class QVBoxLayout;

DUI_BEGIN_NAMESPACE

class DDialogPrivate;
class DDialog : public DAbstractDialog
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QPixmap iconPixmap READ iconPixmap WRITE setIconPixmap)
    Q_PROPERTY(Qt::TextFormat textFormat READ textFormat WRITE setTextFormat NOTIFY textFormatChanged)
    Q_PROPERTY(bool onButtonClickedDone READ onButtonClickedDone WRITE setOnButtonClickedDone)

public:
    explicit DDialog(QWidget *parent = 0);
    explicit DDialog(const QString &title, const QString& message, QWidget *parent = 0);

    int getButtonIndexByText(const QString &text) const;
    int buttonCount() const;
    int contentCount() const;
    QList<QAbstractButton*> getButtons() const;
    QList<QWidget*> getContents() const;
    QAbstractButton* getButton(int index) const;
    QWidget* getContent(int index) const;
    QString title() const;
    QString message() const;
    QIcon icon() const;
    QPixmap iconPixmap() const;
    Qt::TextFormat textFormat() const;
    bool onButtonClickedDone() const;

signals:
    void aboutToClose();
    void closed();
    void buttonClicked(int index, const QString &text);
    void titleChanged(QString title);
    void messageChanged(QString massage);
    void textFormatChanged(Qt::TextFormat textFormat);

public slots:
    int addButton(const QString &text);
    int addButtons(const QStringList &text);
    void insertButton(int index, const QString &text);
    void insertButton(int index, QAbstractButton* button);
    void insertButtons(int index, const QStringList &text);
    void removeButton(int index);
    void removeButton(QAbstractButton *button);
    void removeButtonByText(const QString &text);
    void clearButtons();
    int addContent(QWidget *widget);
    void insertContent(int index, QWidget *widget);
    void removeContent(QWidget *widget, bool isDelete = true);
    void clearContents(bool isDelete = true);
    void setButtonText(int index, const QString &text);
    void setButtonIcon(int index, const QIcon &icon);
    void setTitle(const QString &title);
    void setMessage(const QString& message);
    void setIcon(const QIcon &icon);
    void setIconPixmap(const QPixmap &iconPixmap);
    void setTextFormat(Qt::TextFormat textFormat);
    void setOnButtonClickedDone(bool onButtonClickedDone);
    int exec() Q_DECL_OVERRIDE;

protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DDialog)

    Q_PRIVATE_SLOT(d_func(), void _q_onButtonClicked())
};

DUI_END_NAMESPACE

#endif // DDIALOG_H
