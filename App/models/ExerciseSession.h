#pragma once

/**
 * @brief Association entre une Session et un Exercise.
 */
struct ExerciseSession
{
    int id = -1;
    int sessionId = -1;
    int exerciseId = -1;

    int seriesPlanned = 0;
    int quantityPlanned = 0;
};