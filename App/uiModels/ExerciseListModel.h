#pragma once

#include <QAbstractListModel>
#include <QVector>
#include "../models/Exercise.h"

class ExerciseListModel : public QAbstractListModel
{
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    explicit ExerciseListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setExercises(const QVector<Exercise>& Exercises);
    void addExercise(const Exercise& Exercise);
    Exercise getById(int id) const;
    void removeById(int id);

private:
    QVector<Exercise> m_data;
};

