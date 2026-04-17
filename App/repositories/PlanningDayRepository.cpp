#include "PlanningDayRepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PlanningDayRepository::PlanningDayRepository(QSqlDatabase db, QObject* parent)
    : QObject(parent)
    , m_db(std::move(db))
{}

PlanningDay PlanningDayRepository::getOrCreate(int planningId, const QString& name)
{
    // 1. Chercher un existant
    {
        QSqlQuery q(m_db);
        q.prepare("SELECT id, planning_id, name FROM PlanningDay "
                  "WHERE planning_id = :pid AND name = :name");
        q.bindValue(":pid",  planningId);
        q.bindValue(":name", name);

        if (q.exec() && q.next())
        {
            PlanningDay day;
            day.id         = q.value("id").toInt();
            day.planningId = q.value("planning_id").toInt();
            day.name       = q.value("name").toString();
            return day;
        }
    }

    // 2. Créer si absent
    {
        QSqlQuery q(m_db);
        q.prepare("INSERT INTO PlanningDay (planning_id, name) VALUES (:pid, :name)");
        q.bindValue(":pid",  planningId);
        q.bindValue(":name", name);

        if (!q.exec())
        {
            qWarning() << "PlanningDayRepository::getOrCreate error:" << q.lastError();
            return {};
        }

        PlanningDay day;
        day.id         = q.lastInsertId().toInt();
        day.planningId = planningId;
        day.name       = name;
        return day;
    }
}