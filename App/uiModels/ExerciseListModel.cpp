#include "ExerciseListModel.h"

ExerciseListModel::ExerciseListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int ExerciseListModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

QVariant ExerciseListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return {};

    const Exercise& p = m_data[index.row()];

    switch (role) {
    case IdRole: return p.id;
    case NameRole: return p.name;
    }

    return {};
}

QHash<int, QByteArray> ExerciseListModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "name"}
    };
}

void ExerciseListModel::setExercises(const QVector<Exercise>& Exercises)
{
    beginResetModel();
    m_data = Exercises;
    endResetModel();
}

void ExerciseListModel::addExercise(const Exercise& Exercise)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(Exercise);
    endInsertRows();
}

Exercise ExerciseListModel::getById(int id) const
{
    for (const Exercise& p : m_data)
    {
        if (p.id == id)
            return p;
    }

    return {};
}

void ExerciseListModel::removeById(int id)
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