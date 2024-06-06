cmake_minimum_required(VERSION 3.16)
project(iEDeaL LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Widgets
)
qt_standard_project_setup()

set(SOURCES
    Main.cpp
    MainWindow.cpp
)

set(HEADERS
    MainWindow.h
)

qt_add_executable(iEDeaL ${SOURCES} ${HEADERS})

set_target_properties(iEDeaL
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(iEDeaL
    PUBLIC
        Qt6::Core
        Qt6::Widgets
)
