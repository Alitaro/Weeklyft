#include "DatabasePageViewModel.h"

#include "../repositories/PlanningRepository.h"
#include "../uiModels/PlanningListModel.h"

#include "../repositories/ExerciseRepository.h"
#include "../uiModels/ExerciseListModel.h"
#include "App/models/PlanningDay.h"
#include "App/repositories/SessionRepository.h"
#include "App/repositories/planningdayrepository.h"

#include <QDebug>

/**
 * ViewModel de la page Database
 * - Gère la liste des plannings
 * - Gère la sélection d’un planning
 * - Connecte repository ↔ UI model
 */

static const QStringList DAYS = {
    "Lundi", "Mardi", "Mercredi",
    "Jeudi", "Vendredi", "Samedi", "Dimanche"
};

DatabasePageViewModel::DatabasePageViewModel(PlanningRepository*    planningRepo,
                                             ExerciseRepository*    exerciseRepo,
                                             PlanningDayRepository* planningDayRepo,
                                             SessionRepository*     sessionRepo)
    : QObject(nullptr)
    , m_planningRepo(planningRepo)
    , m_planningModel(new PlanningListModel(this))
    , m_exerciseRepo(exerciseRepo)
    , m_exerciseModel(new ExerciseListModel(this))
    , m_planningDayRepo(planningDayRepo)
    , m_sessionRepo(sessionRepo)
{
    Q_ASSERT(m_planningRepo);
    Q_ASSERT(m_planningDayRepo);
    Q_ASSERT(m_sessionRepo);

    // Chargement initial
    loadPlannings();
    loadExercises();
}

/**
 * Retourne le model exposé à QML (ListView)
 */
QObject* DatabasePageViewModel::planningModel() const
{
    return m_planningModel;
}

// ===============================
// PLANNINGS
// ===============================

/**
 * Charge tous les plannings depuis la base
 */
void DatabasePageViewModel::loadPlannings()
{
    if (!m_planningRepo)
        return;

    qDebug() << "[DatabaseVM] Loading plannings...";

    const QVector<Planning> plannings = m_planningRepo->getAllPlannings();

    m_planningModel->setPlannings(plannings);

    qDebug() << "[DatabaseVM] Plannings loaded:" << plannings.size();
}

/**
 * Crée un planning et l’ajoute directement au model (refresh instant UI)
 */
int DatabasePageViewModel::createPlanning(const QString& name)
{
    if (name.trimmed().isEmpty())
    {
        qDebug() << "[DatabaseVM] createPlanning ignored: empty name";
        return -1;
    }

    if (!m_planningRepo)
        return -1;

    qDebug() << "[DatabaseVM] Creating planning:" << name;

    // 1. Insert en base
    int id = m_planningRepo->createPlanning(name);

    // 2. Construire objet local
    Planning planning;
    planning.id = id;
    planning.name = name;

    // 3. Update UI model instantanément

    m_planningModel->addPlanning(planning);

    qDebug() << "[DatabaseVM] Planning created with id:" << id;

    return id;
}

/**
 * Sélection d’un planning (pour navigation future vers jours)
 */
void DatabasePageViewModel::selectPlanning(int id)
{
    Planning planning = m_planningModel->getById(id);

    if (planning.id == m_selectedPlanning.id)
        return;

    m_selectedPlanning = planning;

    qDebug() << "[DatabaseVM] Selected planning:" << planning.id << planning.name;

    loadDaySessions();

    emit selectedPlanningChanged();
}

void DatabasePageViewModel::deleteSelectedPlanning()
{
    if (!m_planningRepo)
        return;

    if (m_selectedPlanning.id <= 0)
        return;

    int id = m_selectedPlanning.id;

    qDebug() << "[DatabaseVM] Deleting planning:" << id;

    // 1. supprimer en DB
    m_planningRepo->deletePlanning(id);

    // 2. supprimer du model (UI instant)
    m_planningModel->removeById(id);

    // 3. reset sélection
    m_selectedPlanning = {};

    emit selectedPlanningChanged();
}

/**
 * Getter du planning sélectionné
 */
int DatabasePageViewModel::selectedPlanningId() const
{
    return m_selectedPlanning.id;
}

QString DatabasePageViewModel::selectedPlanningName() const
{
    return m_selectedPlanning.name;
}



// ===============================
// EXERCISES
// ===============================

QObject* DatabasePageViewModel::exerciseModel() const
{
    return m_exerciseModel;
}

Q_INVOKABLE void DatabasePageViewModel::loadExercises()
{
    if (!m_exerciseRepo)
        return;

    qDebug() << "[DatabaseVM] Loading exercises...";

    const QVector<Exercise> exercises = m_exerciseRepo->getAllExercises();

    m_exerciseModel->setExercises(exercises);

    qDebug() << "[DatabaseVM] Exercises loaded:" << exercises.size();
}

Q_INVOKABLE int DatabasePageViewModel::createExercise(const QString& name)
{
    if (name.trimmed().isEmpty())
    {
        qDebug() << "[DatabaseVM] createExercise ignored: empty name";
        return -1;
    }

    if (!m_exerciseRepo)
        return -1;

    qDebug() << "[DatabaseVM] Creating exercise:" << name;

    // 1. Insert en base
    int id = m_exerciseRepo->createExercise(name);

    // 2. Construire objet local
    Exercise exercise;
    exercise.id = id;
    exercise.name = name;

    // 3. Update UI model instantanément

    m_exerciseModel->addExercise(exercise);

    qDebug() << "[DatabaseVM] Exercise created with id:" << id;

    return id;
}

Q_INVOKABLE void DatabasePageViewModel::selectExercise(int id)
{
    Exercise exercise = m_exerciseModel->getById(id);

    if (exercise.id == m_selectedExercise.id)
        return;

    m_selectedExercise = exercise;

    qDebug() << "[DatabaseVM] Selected exercise:" << exercise.id << exercise.name;

    emit selectedExerciseChanged();
}


Q_INVOKABLE void DatabasePageViewModel::deleteSelectedExercise()
{
    if (!m_exerciseRepo)
        return;

    if (m_selectedExercise.id <= 0)
        return;

    int id = m_selectedExercise.id;

    qDebug() << "[DatabaseVM] Deleting exercise:" << id;

    // 1. supprimer en DB
    m_exerciseRepo->deleteExercise(id);

    // 2. supprimer du model (UI instant)
    m_exerciseModel->removeById(id);

    // 3. reset sélection
    m_selectedExercise = {};

    emit selectedExerciseChanged();
}

int DatabasePageViewModel::selectedExerciseId() const
{
    return m_selectedExercise.id;
}

QString DatabasePageViewModel::selectedExerciseName() const
{
    return m_selectedExercise.name;
}


// ===============================
// DAYS
// ===============================
void DatabasePageViewModel::selectDay(int index)
{
    if (m_selectedDayIndex == index)
        return;

    m_selectedDayIndex = index;

    emit selectedDayChanged();
}

int DatabasePageViewModel::selectedDayIndex() const
{
    return m_selectedDayIndex;
}

QString DatabasePageViewModel::selectedDayName() const
{
    if (m_selectedDayIndex < 0 || m_selectedDayIndex >= DAYS.size())
        return "";

    return DAYS[m_selectedDayIndex];
}


// ===============================
// SESSIONS
// ===============================
void DatabasePageViewModel::saveSession(const QString& name, const QVariantList& exercises)
{
    if (!m_planningDayRepo || !m_sessionRepo) return;
    if (m_selectedPlanning.id <= 0)            return;
    if (m_selectedDayIndex < 0 || m_selectedDayIndex >= DAYS.size()) return;
    if (name.trimmed().isEmpty())               return;

    const QString& dayName = DAYS[m_selectedDayIndex];

    // 1. Supprimer session existante pour ce jour si elle existe
    Session existing = m_sessionRepo->getSessionForDay(m_selectedPlanning.id, dayName);
    if (existing.id > 0)
        m_sessionRepo->deleteSession(existing.id);

    // 2. Créer ou récupérer le PlanningDay
    const PlanningDay day = m_planningDayRepo->getOrCreate(m_selectedPlanning.id, dayName);
    if (day.id <= 0) return;

    // 3. Créer la Session
    const int sessionId = m_sessionRepo->createSession(day.id, name);
    if (sessionId <= 0) return;

    // 4. Créer les ExerciseSession
    for (const QVariant& entry : exercises)
    {
        const QVariantMap map  = entry.toMap();
        const int exerciseId   = map.value("id", -1).toInt();
        const int series       = map.value("series", 0).toInt();
        const int reps         = map.value("reps", 0).toInt();

        if (exerciseId > 0)
            m_sessionRepo->createExerciseSession(sessionId, exerciseId, series, reps);
    }

    qDebug() << "[DatabaseVM] Session saved, id:" << sessionId;

    // 5. Rafraîchir les données côté QML
    loadDaySessions();
}

void DatabasePageViewModel::loadDaySessions()
{
    m_daySessions.clear();

    for (int i = 0; i < DAYS.size(); ++i)
    {
        const QString& dayName = DAYS[i];

        Session session = m_sessionRepo->getSessionForDay(
            m_selectedPlanning.id, dayName);

        QVariantList exercises;

        if (session.id > 0)
        {
            const auto details = m_sessionRepo->getExerciseDetails(session.id);

            for (const ExerciseSessionDetail& d : details)
            {
                exercises.append(QVariantMap{
                    {"exerciseId",   d.exerciseId},
                    {"exerciseName", d.exerciseName},
                    {"series",       d.series},
                    {"reps",         d.reps}
                });
            }
        }

        m_daySessions.append(QVariantMap{
            {"dayName",     dayName},
            {"sessionId",   session.id},      // -1 si pas de session
            {"sessionName", session.name},
            {"exercises",   exercises}
        });
    }

    emit daySessionsChanged();
}

QVariantList DatabasePageViewModel::daySessions() const
{
    return m_daySessions;
}