#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QVector>

#include "../models/Exercise.h"

/**
 * @brief Accès aux données Exercise.
 */
class ExerciseRepository : public QObject
{
    Q_OBJECT
public:
    ExerciseRepository(QSqlDatabase db,
                       QObject* parent = nullptr);

    /**
     * @brief Crée un nouvel exercice.
     * @return id de l'exercice ou -1 en cas d'erreur
     */
    int createExercise(const QString& name);

    /**
     * @brief Récupère tous les plannings.
     */
    QVector<Exercise> getAllExercises() const;

    /**
     * @brief Supprime un planning.
     */
    bool deleteExercise(int exerciseId);

private:
    QSqlDatabase m_db;
};

