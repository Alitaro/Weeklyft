#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QVector>

#include "../models/Planning.h"

/**
 * @brief Accès aux données Planning.
 */
class PlanningRepository : public QObject
{
    Q_OBJECT

public:
    explicit PlanningRepository(QSqlDatabase db,
                                QObject* parent = nullptr);

    /**
     * @brief Crée un nouveau planning.
     * @return id du planning ou -1 en cas d'erreur
     */
    int createPlanning(const QString& name);

    /**
     * @brief Récupère tous les plannings.
     */
    QVector<Planning> getAllPlannings() const;

    /**
     * @brief Supprime un planning.
     */
    bool deletePlanning(int planningId);

private:
    QSqlDatabase m_db;
};