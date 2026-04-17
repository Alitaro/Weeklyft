#include "SessionRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SessionRepository::SessionRepository(QSqlDatabase db, QObject* parent)
    : QObject(parent)
    , m_db(std::move(db))
{}

int SessionRepository::createSession(int planningDayId, const QString& name)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO Session (planning_day_id, name) VALUES (:did, :name)");
    q.bindValue(":did",  planningDayId);
    q.bindValue(":name", name);

    if (!q.exec())
    {
        qWarning() << "SessionRepository::createSession error:" << q.lastError();
        return -1;
    }

    return q.lastInsertId().toInt();
}

int SessionRepository::createExerciseSession(int sessionId, int exerciseId,
                                             int seriesPlanned, int quantityPlanned)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO ExerciseSession (session_id, exercise_id, series_planned, quantity_planned)
        VALUES (:sid, :eid, :series, :qty)
    )");
    q.bindValue(":sid",    sessionId);
    q.bindValue(":eid",    exerciseId);
    q.bindValue(":series", seriesPlanned);
    q.bindValue(":qty",    quantityPlanned);

    if (!q.exec())
    {
        qWarning() << "SessionRepository::createExerciseSession error:" << q.lastError();
        return -1;
    }

    return q.lastInsertId().toInt();
}

Session SessionRepository::getSessionForDay(int planningId, const QString& dayName) const
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT s.id, s.planning_day_id, s.name
        FROM Session s
        JOIN PlanningDay pd ON pd.id = s.planning_day_id
        WHERE pd.planning_id = :pid AND pd.name = :day
        LIMIT 1
    )");
    q.bindValue(":pid", planningId);
    q.bindValue(":day", dayName);

    if (!q.exec() || !q.next())
        return {};

    Session s;
    s.id           = q.value("id").toInt();
    s.planningDayId = q.value("planning_day_id").toInt();
    s.name         = q.value("name").toString();
    return s;
}

QVector<ExerciseSessionDetail> SessionRepository::getExerciseDetails(int sessionId) const
{
    QVector<ExerciseSessionDetail> result;

    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT es.id, es.exercise_id, e.name, es.series_planned, es.quantity_planned
        FROM ExerciseSession es
        JOIN Exercise e ON e.id = es.exercise_id
        WHERE es.session_id = :sid
    )");
    q.bindValue(":sid", sessionId);

    if (!q.exec())
    {
        qWarning() << "getExerciseDetails error:" << q.lastError();
        return result;
    }

    while (q.next())
    {
        ExerciseSessionDetail d;
        d.exerciseSessionId = q.value("id").toInt();
        d.exerciseId        = q.value("exercise_id").toInt();
        d.exerciseName      = q.value("name").toString();
        d.series            = q.value("series_planned").toInt();
        d.reps              = q.value("quantity_planned").toInt();
        result.append(d);
    }

    return result;
}

bool SessionRepository::deleteSession(int sessionId)
{
    // Supprimer d'abord les ExerciseSession (si pas de CASCADE en DB)
    {
        QSqlQuery q(m_db);
        q.prepare("DELETE FROM ExerciseSession WHERE session_id = :sid");
        q.bindValue(":sid", sessionId);
        if (!q.exec())
            qWarning() << "deleteSession (ExerciseSession) error:" << q.lastError();
    }

    QSqlQuery q(m_db);
    q.prepare("DELETE FROM Session WHERE id = :id");
    q.bindValue(":id", sessionId);

    if (!q.exec())
    {
        qWarning() << "deleteSession error:" << q.lastError();
        return false;
    }

    return true;
}