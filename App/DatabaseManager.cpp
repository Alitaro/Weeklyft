#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::open(const QString& path)
{
    if (QSqlDatabase::contains("main_connection"))
        m_db = QSqlDatabase::database("main_connection");
    else
        m_db = QSqlDatabase::addDatabase("QSQLITE", "main_connection");

    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qCritical() << "DB open error:" << m_db.lastError();
        return false;
    }

    qDebug() << "Database opened:" << path;
    return true;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

void DatabaseManager::initSchema()
{
    QSqlQuery query(m_db);

    // ============================
    // Planning
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Planning (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
        )
    )");

    // ============================
    // PlanningDay
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS PlanningDay (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            planning_id INTEGER,
            name TEXT
        )
    )");

    // ============================
    // Session
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Session (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            planning_day_id INTEGER,
            name TEXT
        )
    )");

    // ============================
    // Exercise
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Exercise (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            type TEXT
        )
    )");

    // ============================
    // ExerciseSession
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS ExerciseSession (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            session_id INTEGER,
            exercise_id INTEGER,
            series_planned INTEGER,
            quantity_planned INTEGER
        )
    )");

    // ============================
    // Quest
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Quest (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            planning_day_id INTEGER,
            name TEXT,
            type TEXT
        )
    )");

    // ============================
    // Week
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Week (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            planning_id INTEGER,
            begin_date TEXT,
            end_date TEXT,
            sport_objectives TEXT,
            objectives TEXT
        )
    )");

    // ============================
    // Day
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS Day (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            week_id INTEGER,
            planning_day_id INTEGER,
            date TEXT,
            report TEXT
        )
    )");

    // ============================
    // ExerciseSessionDay
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS ExerciseSessionDay (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            day_id INTEGER,
            exercise_session_id INTEGER,
            series_done INTEGER,
            quantity_done INTEGER
        )
    )");

    // ============================
    // QuestDay
    // ============================
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS QuestDay (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            day_id INTEGER,
            quest_id INTEGER,
            completed INTEGER
        )
    )");

    qDebug() << "Schema initialized";
}