#ifndef DCOMBOBOXSIMPLEMODEL_H
#define DCOMBOBOXSIMPLEMODEL_H

#include <QObject>
#include <QVariant>
#include <QAbstractItemModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DComboBoxModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DComboBoxModel(QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    QJsonObject getJsonData(int index);
    QModelIndex getModelIndex(int row) const;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int count();
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;
    bool insert(int index, const QJsonObject &dataObj);

    void setProperty(int index, const QString &property, const QVariant &value);
    void set(int index, const QJsonObject &dataObj);
    void append(const QJsonObject &dataObj);
    void remove(int index, int count = 1);
    void clear();

private:
    QJsonArray m_dataArray;
};

DUI_END_NAMESPACE

#endif // DCOMBOBOXSIMPLEMODEL_H
