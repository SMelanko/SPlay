cmake_minimum_required(VERSION 2.8)

project(STest)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -pthread")
endif()

if(MSVC)
	add_definitions(/W3)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -pedantic)
else()
	message("Unknown compiler")
endif()

find_package(Qt5Widgets)

if(Qt5Widgets_FOUND)
	include_directories(${Qt5Widgets_INCLUDE_DIRS})
	add_definitions(${Qt5Widgets_DEFINITIONS})

	set(CMake_QT_LIBRARIES
		${Qt5Widgets_LIBRARIES})
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
	
	if(WIN32 AND TARGET Qt5::Core)
		get_property(_Qt5_Core_LOCATION TARGET Qt5::Core PROPERTY LOCATION)
		get_filename_component(Qt_BIN_DIR "${_Qt5_Core_LOCATION}" PATH)
	endif()
else()
	message(FATAL_ERROR "Qt5 package was not found")
endif()

set(INCLUDE_LIST
	include/Application.h
	include/Common.h
	include/Logger.h
	include/MainWindow.h)

set(cppformat_INCLUDE_LIST
	include/cppformat/format.h)

set(SRC_LIST
	src/Application.cpp
	src/Logger.cpp
	src/main.cpp
	src/MainWindow.cpp)

set(cppformat_SRC_LIST
	src/cppformat/format.cc)
	
qt5_wrap_cpp(MOC_SRC_LIST
	include/Application.h
	include/MainWindow.h)

source_group("Header Files" FILES ${INCLUDE_LIST})
source_group("Header Files\\cppformat" FILES ${cppformat_INCLUDE_LIST})
source_group("Source Files" FILES ${SRC_LIST})
source_group("Source Files\\MOC" FILES ${MOC_SRC_LIST})
source_group("Source Files\\cppformat" FILES ${cppformat_SRC_LIST})

#
# Third party include derictories.
#
set(external_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${external_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
	${INCLUDE_LIST}
	${cppformat_INCLUDE_LIST}
	#${external_INCLUDE_DIRS}
	${SRC_LIST}
	${MOC_SRC_LIST}
	${cppformat_SRC_LIST})

target_link_libraries(${PROJECT_NAME}
	${Qt5Core_QTMAIN_LIBRARIES}
	${CMake_QT_LIBRARIES}
)
	
if(Qt_BIN_DIR)
	set_property(TARGET ${PROJECT_NAME} PROPERTY Qt_BIN_DIR ${Qt_BIN_DIR})
endif()
