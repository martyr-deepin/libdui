#ifndef DINPUTDIALOG_H
#define DINPUTDIALOG_H

#include <QInputDialog>

#include "ddialog.h"
#include "dlineedit.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DInputDialogPrivate;
class DInputDialog : public DDialog
{
    Q_OBJECT

    Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode)
    Q_PROPERTY(QString labelText READ labelText WRITE setLabelText NOTIFY labelTextChanged)
    Q_PROPERTY(QString textValue READ textValue WRITE setTextValue NOTIFY textValueChanged)
    Q_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY intValueChanged)
    Q_PROPERTY(int doubleValue READ doubleValue WRITE setDoubleValue NOTIFY doubleValueChanged)
    Q_PROPERTY(DLineEdit::EchoMode textEchoMode READ textEchoMode WRITE setTextEchoMode)
    Q_PROPERTY(bool comboBoxEditable READ isComboBoxEditable WRITE setComboBoxEditable)
    Q_PROPERTY(QStringList comboBoxItems READ comboBoxItems WRITE setComboBoxItems)
    Q_PROPERTY(int comboBoxCurrentIndex READ comboBoxCurrentIndex WRITE setComboBoxCurrentIndex NOTIFY comboBoxCurrentIndexChanged)
    Q_PROPERTY(int intMinimum READ intMinimum WRITE setIntMinimum)
    Q_PROPERTY(int intMaximum READ intMaximum WRITE setIntMaximum)
    Q_PROPERTY(int intStep READ intStep WRITE setIntStep)
    Q_PROPERTY(double doubleMinimum READ doubleMinimum WRITE setDoubleMinimum)
    Q_PROPERTY(double doubleMaximum READ doubleMaximum WRITE setDoubleMaximum)
    Q_PROPERTY(int doubleDecimals READ doubleDecimals WRITE setDoubleDecimals)
    Q_PROPERTY(QString okButtonText READ okButtonText WRITE setOkButtonText)
    Q_PROPERTY(QString cancelButtonText READ cancelButtonText WRITE setCancelButtonText)

public:
    enum InputMode {
        TextInput,
        ComboBox,
        IntInput,
        DoubleInput
    };

    explicit DInputDialog(QWidget *parent = 0);

    void setInputMode(InputMode mode);
    InputMode inputMode() const;

    void setTextValue(const QString &text);
    QString textValue() const;

    QString labelText() const;
    void setLabelText(QString labelText);

    void setTextEchoMode(QLineEdit::EchoMode mode);
    QLineEdit::EchoMode textEchoMode() const;

    void setComboBoxEditable(bool editable);
    bool isComboBoxEditable() const;

    void setComboBoxItems(const QStringList &items);
    QStringList comboBoxItems() const;

    int comboBoxCurrentIndex() const;
    void setComboBoxCurrentIndex(int comboBoxCurrentIndex);

    void setIntValue(int value);
    int intValue() const;

    void setIntMinimum(int min);
    int intMinimum() const;

    void setIntMaximum(int max);
    int intMaximum() const;

    void setIntRange(int min, int max);

    void setIntStep(int step);
    int intStep() const;

    void setDoubleValue(double value);
    double doubleValue() const;

    void setDoubleMinimum(double min);
    double doubleMinimum() const;

    void setDoubleMaximum(double max);
    double doubleMaximum() const;

    void setDoubleRange(double min, double max);

    void setDoubleDecimals(int decimals);
    int doubleDecimals() const;

    void setOkButtonText(const QString &text);
    QString okButtonText() const;

    void setCancelButtonText(const QString &text);
    QString cancelButtonText() const;

    static QString getText(QWidget *parent, const QString &title, const QString &label,
                           QLineEdit::EchoMode echo = QLineEdit::Normal,
                           const QString &text = QString(), bool *ok = 0, Qt::WindowFlags flags = 0,
                           Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

    static QString getItem(QWidget *parent, const QString &title, const QString &label,
                           const QStringList &items, int current = 0, bool editable = true,
                           bool *ok = 0, Qt::WindowFlags flags = 0,
                           Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

    static int getInt(QWidget *parent, const QString &title, const QString &label, int value = 0,
                      int minValue = -2147483647, int maxValue = 2147483647,
                      int step = 1, bool *ok = 0, Qt::WindowFlags flags = 0);
    static double getDouble(QWidget *parent, const QString &title, const QString &label, double value = 0,
                            double minValue = -2147483647, double maxValue = 2147483647,
                            int decimals = 1, bool *ok = 0, Qt::WindowFlags flags = 0);

#if QT_DEPRECATED_SINCE(5, 0)
    QT_DEPRECATED static inline int getInteger(QWidget *parent, const QString &title, const QString &label, int value = 0,
                          int minValue = -2147483647, int maxValue = 2147483647,
                          int step = 1, bool *ok = 0, Qt::WindowFlags flags = 0)
    {
        return getInt(parent, title, label, value, minValue, maxValue, step, ok, flags);
    }
#endif

Q_SIGNALS:
    // ### emit signals!
    void textValueChanged(const QString &text);
    void textValueSelected(const QString &text);
    void labelTextChanged(QString labelText);
    void intValueChanged(int value);
    void intValueSelected(int value);
    void doubleValueChanged(double value);
    void doubleValueSelected(double value);
    void cancelButtonClicked();
    void okButtonClicked();
    void comboBoxCurrentIndexChanged(int comboBoxCurrentIndex);

private:
    D_DECLARE_PRIVATE(DInputDialog)
};

DUI_END_NAMESPACE

#endif // DINPUTDIALOG_H
