cmake_minimum_required(VERSION 2.8)

project(STest)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(MSVC)
	add_definitions(/W3)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -pedantic)
else()
	message("Unknown compiler")
endif()

find_package(Qt5Widgets QUIET)

if(Qt5Widgets_FOUND)
	message(STATUS "Qt5 package found")

	#include_directories(${Qt5Widgets_INCLUDE_DIRS})
	message(STATUS "${Qt5Widgets_INCLUDE_DIRS}")
	#/usr/include/x86_64-linux-gnu/qt5/;
	#/usr/include/x86_64-linux-gnu/qt5/QtWidgets;
	#/usr/include/x86_64-linux-gnu/qt5/QtGui;
	#/usr/include/x86_64-linux-gnu/qt5/QtCore;
	#/usr/lib/x86_64-linux-gnu/qt5//mkspecs/linux-g++-64

	#add_definitions(${Qt5Widgets_DEFINITIONS})
	message(STATUS "${Qt5Widgets_DEFINITIONS}")
	#-DQT_WIDGETS_LIB;
	#-DQT_GUI_LIB;
	#-DQT_CORE_LIB

	#set(CMake_QT_LIBRARIES ${Qt5Widgets_LIBRARIES})
	#set(QT_QTMAIN_LIBRARY ${Qt5Core_QTMAIN_LIBRARIES})
else()
	message(FATAL_ERROR "Qt5 package was not found")
endif()

set(INCLUDE_LIST
	include/Aux.h
	include/format.h)

set(SRC_LIST
	src/Aux.cpp
	src/format.cc
	src/main.cpp)

source_group("Header Files" FILES ${INCLUDE_LIST})
source_group("Source Files" FILES ${SRC_LIST})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
	${INCLUDE_LIST}
	${SRC_LIST})

