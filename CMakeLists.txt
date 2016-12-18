cmake_minimum_required(VERSION 2.8)

find_package(Qt5 COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SERVER_SRCS 
    main.cpp
    mainwindow.cpp
    mapconfigwidget.cpp
)

set(SERVER_HEADERS
    maxscoreconfigwidget.h
    maxplayersconfigwidget.h
    teamdamageconfigwidget.h
    servernameconfigwidget.h
    lanconfigwidget.h
    timelimitconfigwidget.h
    configwidget.h
    mainwindow.h
    mapconfigwidget.h
    passwordconfigwidget.h
    gametypeconfigwidget.h
)

add_executable(teeworldsserver ${SERVER_SRCS} ${SERVER_HEADERS} teeworldsserver.qrc)

target_link_libraries(teeworldsserver Qt5::Core Qt5::Widgets)
