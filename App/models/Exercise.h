#pragma once

#include <QString>
#include "types.h"

/**
 * @brief Exercice disponible.
 */
struct Exercise
{
    int id = -1;
    QString name;

    ExerciseType type = ExerciseType::Repetitions;
};