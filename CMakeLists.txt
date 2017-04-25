cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0020 NEW)

find_package(Qt5 COMPONENTS Core Widgets Gui)

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

# copy dlls
if(WIN32)
	foreach(QTLIB Qt5::Widgets Qt5::Core Qt5::Gui)

		add_custom_command(
		TARGET teeworldsserver POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:${QTLIB}>
			$<TARGET_FILE_DIR:teeworldsserver>
		)
	
	endforeach()
	
	
endif()

