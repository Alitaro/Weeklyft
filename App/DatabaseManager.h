#pragma once

#include <QSqlDatabase>
#include <QString>

/**
 * @brief Gère l'initialisation et l'accès à la base de données.
 */
class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool open(const QString& path);

    QSqlDatabase database() const;

    void initSchema();

private:
    DatabaseManager() = default;

    QSqlDatabase m_db;
};