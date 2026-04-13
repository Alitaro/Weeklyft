#include "PlanningListModel.h"

PlanningListModel::PlanningListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int PlanningListModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

QVariant PlanningListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return {};

    const Planning& p = m_data[index.row()];

    switch (role) {
    case IdRole: return p.id;
    case NameRole: return p.name;
    }

    return {};
}

QHash<int, QByteArray> PlanningListModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "name"}
    };
}

void PlanningListModel::setPlannings(const QVector<Planning>& plannings)
{
    beginResetModel();
    m_data = plannings;
    endResetModel();
}

void PlanningListModel::addPlanning(const Planning& planning)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(planning);
    endInsertRows();
}

Planning PlanningListModel::getById(int id) const
{
    for (const Planning& p : m_data)
    {
        if (p.id == id)
            return p;
    }

    return {};
}

void PlanningListModel::removeById(int id)
{
    for (int i = 0; i < m_data.size(); ++i)
    {
        if (m_data[i].id == id)
        {
            beginRemoveRows(QModelIndex(), i, i);
            m_data.removeAt(i);
            endRemoveRows();
            return;
        }
    }
}