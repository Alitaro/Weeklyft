#include "ExerciseRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

ExerciseRepository::ExerciseRepository(QSqlDatabase db,
                                       QObject* parent)
    : QObject(parent),
    m_db(std::move(db))
{
}

// ============================
// CREATE
// ============================

int ExerciseRepository::createExercise(const QString& name)
{
    QSqlQuery query(m_db);

    query.prepare(R"(
        INSERT INTO Exercise (name)
        VALUES (:name)
    )");

    query.bindValue(":name", name);

    if (!query.exec()) {
        qWarning() << "createExercise error:" << query.lastError();
        return -1;
    }

    return query.lastInsertId().toInt();
}

// ============================
// READ
// ============================

QVector<Exercise> ExerciseRepository::getAllExercises() const
{
    QVector<Exercise> result;

    QSqlQuery query(m_db);

    if (!query.exec("SELECT id, name FROM Exercise")) {
        qWarning() << "getAllExercises error:" << query.lastError();
        return result;
    }

    while (query.next()) {
        Exercise p;
        p.id = query.value("id").toInt();
        p.name = query.value("name").toString();

        result.append(p);
    }

    return result;
}

// ============================
// DELETE
// ============================

bool ExerciseRepository::deleteExercise(int ExerciseId)
{
    QSqlQuery query(m_db);

    query.prepare("DELETE FROM Exercise WHERE id = :id");
    query.bindValue(":id", ExerciseId);

    if (!query.exec()) {
        qWarning() << "deleteExercise error:" << query.lastError();
        return false;
    }

    return true;
}