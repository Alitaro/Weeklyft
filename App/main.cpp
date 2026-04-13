#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "DatabaseManager.h"
#include "repositories/PlanningRepository.h"
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
    // Repos
    // ============================
    auto planningRepo = new PlanningRepository(db);

    // ============================
    // QML
    // ============================
    QQmlApplicationEngine engine;
    engine.loadFromModule("Weeklyft", "App");

    return app.exec();
}