#pragma once

#include <QString>

/**
 * @brief Séance sportive associée à un PlanningDay.
 */
struct Session
{
    int id = -1;
    int planningDayId = -1;
    QString name;
};