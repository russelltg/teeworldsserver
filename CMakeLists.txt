cmake_minimum_required(VERSION 2.8)

find_package(Qt5 COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(teeworldsserver configwidget.h gametypeconfigwidget.h lanconfigwidget.h main.cpp mainwindow.cpp mainwindow.h maxplayersconfigwidget.h)

target_link_libraries(teeworldsserver Qt5::Core Qt5::Widgets)
