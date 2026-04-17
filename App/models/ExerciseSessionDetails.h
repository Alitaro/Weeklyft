#pragma once
#include <QString>

/**
 * @brief DTO enrichi pour affichage UI.
 */
struct ExerciseSessionDetail
{
    int     exerciseSessionId = -1;
    int     exerciseId        = -1;
    QString exerciseName;
    int     series            = 0;
    int     reps              = 0;
};