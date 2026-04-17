#pragma once

#include <QObject>
#include <QSqlDatabase>
#include "../models/PlanningDay.h"

class PlanningDayRepository : public QObject
{
    Q_OBJECT

public:
    explicit PlanningDayRepository(QSqlDatabase db, QObject* parent = nullptr);

    /**
     * @brief Retourne le PlanningDay correspondant à (planningId, name),
     *        ou en crée un s'il n'existe pas encore.
     */
    PlanningDay getOrCreate(int planningId, const QString& name);

private:
    QSqlDatabase m_db;
};