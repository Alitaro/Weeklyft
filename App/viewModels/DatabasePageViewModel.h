#pragma once

#include "App/models/Planning.h"
#include <QObject>

class PlanningRepository;
class PlanningListModel;

/**
 * ViewModel de la page Database
 * - Expose les plannings à QML
 * - Gère création + sélection
 * - Interface entre Repository et UI
 */
class DatabasePageViewModel : public QObject
{
    Q_OBJECT

    // Model exposé à QML (ListView)
    Q_PROPERTY(QObject* planningModel READ planningModel CONSTANT)

    // ID du planning actuellement sélectionné
    Q_PROPERTY(int selectedPlanningId READ selectedPlanningId NOTIFY selectedPlanningChanged)
    Q_PROPERTY(QString selectedPlanningName READ selectedPlanningName NOTIFY selectedPlanningChanged)


public:
    explicit DatabasePageViewModel(PlanningRepository* planningRepo);

    // ===============================
    // PLANNINGS
    // ===============================
    /**
     * Retourne le model QML (ListView)
     */
    QObject* planningModel() const;

    /**
     * Charge tous les plannings depuis la DB
     */
    Q_INVOKABLE void loadPlannings();

    /**
     * Crée un nouveau planning
     */
    Q_INVOKABLE int createPlanning(const QString& name);

    /**
     * Sélectionne un planning (navigation future)
     */
    Q_INVOKABLE void selectPlanning(int id);


    Q_INVOKABLE void deleteSelectedPlanning();
    /**
     * Getter sélection
     */
    int selectedPlanningId() const;
    QString selectedPlanningName() const;


signals:
    /**
     * Notifie changement de planning sélectionné
     */
    void selectedPlanningChanged();

private:
    // ===============================
    // PLANNINGS
    // ===============================
    PlanningRepository* m_planningRepo = nullptr;

    // Model exposé à QML
    PlanningListModel* m_planningModel = nullptr;

    // State UI
    Planning m_selectedPlanning;
};