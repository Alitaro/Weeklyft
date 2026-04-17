#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "App/repositories/PlanningDayRepository.h"
#include "App/repositories/SessionRepository.h"
#include "DatabaseManager.h"
#include "repositories/PlanningRepository.h"
#include "repositories/ExerciseRepository.h"
#include "viewmodels/DatabasePageViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    // ============================
    // DB
    // ============================
    auto& dbManager = DatabaseManager::instance();

    if (!dbManager.open("weeklyft.db"))
        return -1;

    dbManager.initSchema();

    auto db = dbManager.database();

    // ============================
    // Repositories
    // ============================
    auto planningRepo = new PlanningRepository(db);
    auto exerciseRepo = new ExerciseRepository(db);
    auto planningDayRepo = new PlanningDayRepository(db);
    auto sessionRepo = new SessionRepository(db);

    // ============================
    // ViewModel
    // ============================
    auto databaseVM = new DatabasePageViewModel(planningRepo, exerciseRepo, planningDayRepo, sessionRepo);

    // ============================
    // QML
    // ============================
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("databaseVM", databaseVM);
    engine.loadFromModule("Weeklyft", "App");

    return app.exec();
}