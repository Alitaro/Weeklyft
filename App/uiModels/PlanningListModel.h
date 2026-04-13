#pragma once

#include <QAbstractListModel>
#include <QVector>
#include "../models/Planning.h"

/**
 * Model Qt exposé à QML (ListView)
 */
class PlanningListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    explicit PlanningListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setPlannings(const QVector<Planning>& plannings);
    void addPlanning(const Planning& planning);
    Planning getById(int id) const;
    void removeById(int id);

private:
    QVector<Planning> m_data;
};