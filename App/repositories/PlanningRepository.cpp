#include "PlanningRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

PlanningRepository::PlanningRepository(QSqlDatabase db,
                                       QObject* parent)
    : QObject(parent),
    m_db(std::move(db))
{
}

// ============================
// CREATE
// ============================

int PlanningRepository::createPlanning(const QString& name)
{
    QSqlQuery query(m_db);

    query.prepare(R"(
        INSERT INTO Planning (name)
        VALUES (:name)
    )");

    query.bindValue(":name", name);

    if (!query.exec()) {
        qWarning() << "createPlanning error:" << query.lastError();
        return -1;
    }

    return query.lastInsertId().toInt();
}

// ============================
// READ
// ============================

QVector<Planning> PlanningRepository::getAllPlannings() const
{
    QVector<Planning> result;

    QSqlQuery query(m_db);

    if (!query.exec("SELECT id, name FROM Planning")) {
        qWarning() << "getAllPlannings error:" << query.lastError();
        return result;
    }

    while (query.next()) {
        Planning p;
        p.id = query.value("id").toInt();
        p.name = query.value("name").toString();

        result.append(p);
    }

    return result;
}

// ============================
// DELETE
// ============================

bool PlanningRepository::deletePlanning(int planningId)
{
    QSqlQuery query(m_db);

    query.prepare("DELETE FROM Planning WHERE id = :id");
    query.bindValue(":id", planningId);

    if (!query.exec()) {
        qWarning() << "deletePlanning error:" << query.lastError();
        return false;
    }

    return true;
}