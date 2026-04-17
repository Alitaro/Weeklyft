#pragma once

#include <QObject>
#include <QSqlDatabase>
#include "../models/Session.h"
#include "../models/ExerciseSession.h"
#include "../models/ExerciseSessionDetails.h"

class SessionRepository : public QObject
{
    Q_OBJECT

public:
    explicit SessionRepository(QSqlDatabase db, QObject* parent = nullptr);

    /**
     * @brief Crée une Session liée à un PlanningDay.
     * @return id inséré ou -1
     */
    int createSession(int planningDayId, const QString& name);

    /**
     * @brief Crée un lien ExerciseSession.
     * @return id inséré ou -1
     */
    int createExerciseSession(int sessionId, int exerciseId,
                              int seriesPlanned, int quantityPlanned);

    Session getSessionForDay(int planningId, const QString& dayName) const;
    QVector<ExerciseSessionDetail> getExerciseDetails(int sessionId) const;
    bool deleteSession(int sessionId);

private:
    QSqlDatabase m_db;
};