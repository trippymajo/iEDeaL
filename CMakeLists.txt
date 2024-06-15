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
    EdlFile.cpp
)

set(HEADERS
    MainWindow.h
    EdlFile.h
)

qt_add_executable(iEDeaL ${SOURCES} ${HEADERS})

if(MSVC OR (CMAKE_CXX_COMPILER_ID STREQUALCMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")) 
    target_sources(iEDeaL PRIVATE stdafx.cpp)
    target_precompile_headers(iEDeaL PRIVATE stdafx.h)
else()
    message(FATAL_ERROR "Your compiler does not support precompiled headers. Ha-ha!")
endif()

set_target_properties(iEDeaL
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(iEDeaL
    PUBLIC
        Qt6::Core
        Qt6::Widgets
)
