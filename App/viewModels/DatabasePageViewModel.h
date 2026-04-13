#pragma once

#include "App/models/Planning.h"
#include "App/models/Exercise.h"
#include <QObject>

class PlanningRepository;
class PlanningListModel;

class ExerciseRepository;
class ExerciseListModel;

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


    Q_PROPERTY(QObject* exerciseModel READ exerciseModel CONSTANT)

    // ID du planning actuellement sélectionné
    Q_PROPERTY(int selectedExerciseId READ selectedExerciseId NOTIFY selectedExerciseChanged)
    Q_PROPERTY(QString selectedExerciseName READ selectedExerciseName NOTIFY selectedExerciseChanged)


public:
    explicit DatabasePageViewModel(PlanningRepository* planningRepo, ExerciseRepository* exerciseRepo);

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


    // ===============================
    // EXERCISES
    // ===============================
    QObject* exerciseModel() const;

    Q_INVOKABLE void loadExercises();

    Q_INVOKABLE int createExercise(const QString& name);

    Q_INVOKABLE void selectExercise(int id);


    Q_INVOKABLE void deleteSelectedExercise();

    int selectedExerciseId() const;
    QString selectedExerciseName() const;


signals:
    /**
     * Notifie changement de planning sélectionné
     */
    void selectedPlanningChanged();
    void selectedExerciseChanged();

private:
    // ===============================
    // PLANNINGS
    // ===============================
    PlanningRepository* m_planningRepo = nullptr;

    // Model exposé à QML
    PlanningListModel* m_planningModel = nullptr;

    // State UI
    Planning m_selectedPlanning;


    // ===============================
    // EXERCISES
    // ===============================
    ExerciseRepository* m_exerciseRepo = nullptr;

    // Model exposé à QML
    ExerciseListModel* m_exerciseModel = nullptr;

    // State UI
    Exercise m_selectedExercise;
};