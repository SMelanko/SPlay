cmake_minimum_required(VERSION 2.8)

project(STest)

if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING
		"None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -pthread")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(MSVC)
	add_definitions(/W3)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -pedantic)
else()
	message("Unknown compiler")
endif()

find_package(Qt5Widgets)
find_package(Qt5Multimedia)

if(Qt5Widgets_FOUND AND Qt5Multimedia_FOUND)
	set(QT5_INCLUDES
		${Qt5Widgets_INCLUDE_DIRS}
		${Qt5Multimedia_INCLUDE_DIRS})
	include_directories(${QT5_INCLUDES})
	message(STATUS "Qt include list: ${QT5_INCLUDES}")
	add_definitions(
		${Qt5Widgets_DEFINITIONS}
		${Qt5Multimedia_DEFINITIONS})

	set(CMake_QT_LIBRARIES
		${Qt5Widgets_LIBRARIES}
		${Qt5Multimedia_LIBRARIES})
	message(STATUS "Qt library list: ${CMake_QT_LIBRARIES}")

	message(STATUS "Cxx flags: ${CMAKE_CXX_FLAGS}")

	if(WIN32 AND TARGET Qt5::Core)
		get_property(_Qt5_Core_LOCATION TARGET Qt5::Core PROPERTY LOCATION)
		get_filename_component(Qt_BIN_DIR "${_Qt5_Core_LOCATION}" PATH)
	endif()
else()
	message(FATAL_ERROR "The Qt5 package was not found")
endif()

find_package(taglib)

if (NOT taglib_found)
	message(FATAL_ERROR "The taglib library was not found")
endif ()

set(INCLUDE_LIST
	include/Application.h
	include/Logger.h
	include/MainWindow.h
	include/PlaylistModel.h
	include/PlaylistView.h
	include/Slider.h
#	include/Track.h
	include/Types.h
	include/VolumeButton.h)

set(SRC_LIST
	src/Application.cpp
	src/Logger.cpp
	src/main.cpp
	src/MainWindow.cpp
	src/PlaylistModel.cpp
	src/PlaylistView.cpp
	src/Slider.cpp
#	src/Track.cpp
	src/VolumeButton.cpp)

qt5_wrap_cpp(MOC_SRC_LIST
	include/Application.h
	include/MainWindow.h
	include/PlaylistModel.h
	include/PlaylistView.h
	include/VolumeButton.h)

qt5_add_resources(RES_LIST
	res/SPlay.qrc)

source_group("Header Files" FILES ${INCLUDE_LIST})
source_group("Source Files" FILES ${SRC_LIST})
source_group("Source Files\\MOC" FILES ${MOC_SRC_LIST})
source_group("Resource Files" FILES ${RES_LIST})

#
# Third party include derictories.
#
set(external_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${external_INCLUDE_DIRS}
	${taglib_include_dirs})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
	${INCLUDE_LIST}
	${SRC_LIST}
	${MOC_SRC_LIST}
	${RES_LIST})

target_link_libraries(${PROJECT_NAME}
	${Qt5Core_QTMAIN_LIBRARIES}
	${CMake_QT_LIBRARIES}
	${taglib_libraries}
)
	
if(Qt_BIN_DIR)
	set_property(TARGET ${PROJECT_NAME} PROPERTY Qt_BIN_DIR ${Qt_BIN_DIR})
endif()
