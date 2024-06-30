cmake_minimum_required(VERSION 3.16)

project(iEDeaL VERSION 0.1 LANGUAGES CXX)

#CMAKE_AUTOMOC
set(CMAKE_AUTOMOC ON)

#This only possinble when you build qt's libraries yourself with -static flag
#set(QT_STATIC ON)

#C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#Headers & Sources
set(SOURCES
    Main.cpp
    MainWindow.cpp
    EdlFile.cpp)
set(HEADERS
    MainWindow.h
    EdlFile.h)

#Exe
qt_add_executable(iEDeaL ${SOURCES} ${HEADERS})

#Link
target_link_libraries(iEDeaL PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(iEDeaL PROPERTIES WIN32_EXECUTABLE TRUE)

if(MSVC OR (CMAKE_CXX_COMPILER_ID STREQUALCMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")) 
    target_sources(iEDeaL PRIVATE stdafx.cpp)
    target_precompile_headers(iEDeaL PRIVATE stdafx.h)
else()
    message(FATAL_ERROR "Your compiler does not support precompiled headers. Ha-ha!")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

#place needed qt files near exe
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    include(deployqt)
    windeployqt(iEDeaL)
endif()
