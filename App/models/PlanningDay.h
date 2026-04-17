#pragma once

#include <QString>

/**
 * @brief Jour d’un planning (template).
 */
struct PlanningDay
{
    int id = -1;
    int planningId = -1;
    QString name;
};