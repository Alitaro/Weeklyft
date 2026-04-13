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
)