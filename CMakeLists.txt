cmake_minimum_required(VERSION 3.21)
project(WeeklyftApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    QuickControls2
    Sql
)

qt_standard_project_setup()

# ============================
# 1. CREATE TARGET (IMPORTANT FIRST)
# ============================
qt_add_executable(WeeklyftApp
    ${CMAKE_SOURCE_DIR}/App/main.cpp
    ${CMAKE_SOURCE_DIR}/App/DatabaseManager.cpp
    ${CMAKE_SOURCE_DIR}/App/DatabaseManager.h
    ${CMAKE_SOURCE_DIR}/App/models/Planning.h
    ${CMAKE_SOURCE_DIR}/App/models/Exercise.h
    ${CMAKE_SOURCE_DIR}/App/models/Session.h
    ${CMAKE_SOURCE_DIR}/App/models/ExerciseSession.h
    ${CMAKE_SOURCE_DIR}/App/repositories/PlanningRepository.cpp
    ${CMAKE_SOURCE_DIR}/App/repositories/PlanningRepository.h
    ${CMAKE_SOURCE_DIR}/App/repositories/PlanningDayRepository.h
    ${CMAKE_SOURCE_DIR}/App/repositories/PlanningDayRepository.cpp
    ${CMAKE_SOURCE_DIR}/App/repositories/SessionRepository.h
    ${CMAKE_SOURCE_DIR}/App/repositories/SessionRepository.cpp
    ${CMAKE_SOURCE_DIR}/App/uiModels/PlanningListModel.cpp
    ${CMAKE_SOURCE_DIR}/App/uiModels/PlanningListModel.h
    ${CMAKE_SOURCE_DIR}/App/repositories/ExerciseRepository.cpp
    ${CMAKE_SOURCE_DIR}/App/repositories/ExerciseRepository.cpp
    ${CMAKE_SOURCE_DIR}/App/repositories/ExerciseRepository.h
    ${CMAKE_SOURCE_DIR}/App/uiModels/ExerciseListModel.cpp
    ${CMAKE_SOURCE_DIR}/App/uiModels/ExerciseListModel.h
    ${CMAKE_SOURCE_DIR}/App/viewModels/DatabasePageViewModel.cpp
    ${CMAKE_SOURCE_DIR}/App/viewModels/DatabasePageViewModel.h
)

# ============================
# 2. LINK (ONLY AFTER TARGET EXISTS)
# ============================
target_link_libraries(WeeklyftApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
)

# ============================
# 3. QML MODULE
# ============================
qt_add_qml_module(WeeklyftApp
    URI Weeklyft
    VERSION 1.0

    QML_FILES
        WeeklyftContent/App.qml
        WeeklyftContent/DatabasePage.qml
        WeeklyftContent/PlanningDaysPage.qml
        WeeklyftContent/DayEditPage.qml
)