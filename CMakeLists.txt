cmake_minimum_required(VERSION 2.8)

project(STest)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

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
	)

set(cppformat_INCLUDE_LIST
	include/cppformat/format.h)

set(spdlog_details_INCLUDE_LIST
	include/spdlog/details/async_log_helper.h
	include/spdlog/details/async_logger_impl.h
	include/spdlog/details/file_helper.h
	include/spdlog/details/line_logger.h
	include/spdlog/details/log_msg.h
	include/spdlog/details/logger_impl.h
	include/spdlog/details/mpmc_bounded_q.h
	include/spdlog/details/null_mutex.h
	include/spdlog/details/os.h
	include/spdlog/details/pattern_formatter_impl.h
	include/spdlog/details/registry.h
	include/spdlog/details/spdlog_impl.h)
	
set(spdlog_sinks_INCLUDE_LIST
	include/spdlog/sinks/android_sink.h
	include/spdlog/sinks/base_sink.h
	include/spdlog/sinks/dist_sink.h
	include/spdlog/sinks/file_sinks.h
	include/spdlog/sinks/null_sink.h
	include/spdlog/sinks/ostream_sink.h
	include/spdlog/sinks/sink.h
	include/spdlog/sinks/stdout_sinks.h
	include/spdlog/sinks/syslog_sink.h)

set(spdlog_INCLUDE_LIST
	include/spdlog/async_logger.h
	include/spdlog/common.h
	include/spdlog/formatter.h
	include/spdlog/logger.h
	include/spdlog/spdlog.h
	include/spdlog/tweakme.h)

set(SRC_LIST
	src/main.cpp)

set(cppformat_SRC_LIST
	src/cppformat/format.cc)

source_group("Header Files" FILES ${INCLUDE_LIST})
source_group("Header Files\\cppformat" FILES ${cppformat_INCLUDE_LIST})
source_group("Header Files\\spdlog" FILES ${spdlog_INCLUDE_LIST})
source_group("Header Files\\spdlog\\details" FILES ${spdlog_details_INCLUDE_LIST})
source_group("Header Files\\spdlog\\sinks" FILES ${spdlog_sinks_INCLUDE_LIST})
source_group("Source Files" FILES ${SRC_LIST})
source_group("Source Files\\cppformat" FILES ${cppformat_SRC_LIST})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
	${INCLUDE_LIST}
	${cppformat_INCLUDE_LIST}
	${spdlog_INCLUDE_LIST}
	${spdlog_details_INCLUDE_LIST}
	${spdlog_sinks_INCLUDE_LIST}
	${SRC_LIST}
	${cppformat_SRC_LIST})

