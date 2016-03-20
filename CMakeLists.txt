cmake_minimum_required (VERSION 2.8)

project (SPlay)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE Debug)
endif ()

message (STATUS "Generate ${CMAKE_BUILD_TYPE} version")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	# Using Clang.
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# Using GCC.
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -pthread")
	add_definitions (-Wall -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	# Using Intel C++.
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# Using Visual Studio C++.
	add_definitions (/W3)
else ()
	message (FATAL_ERROR "Unknown compiler")
endif ()

#
# Find Qt5 framework.
#
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

#
# Find TagLib library.
#
find_package (Taglib)
add_definitions (-DTAGLIB_STATIC)

#
# Third party include derictories.
#
set (EXTERNAL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external")

set (INCLUDE_LIST
	include/Application.h
	include/Logger.h
	include/MainWindow.h
	include/PlaybackControlButton.h
	include/PlaylistModel.h
	include/PlaylistView.h
	include/PlaylistViewDelegate.h
	include/Slider.h
	include/Types.h
	include/Utils.h
	include/VolumeWidget.h)

set (SRC_LIST
	src/Application.cpp
	src/Logger.cpp
	src/main.cpp
	src/MainWindow.cpp
	src/PlaylistModel.cpp
	src/PlaylistView.cpp
	src/PlaylistViewDelegate.cpp
	src/Slider.cpp
	src/Utils.cpp
	src/VolumeWidget.cpp)

qt5_wrap_cpp (MOC_SRC_LIST
	include/Application.h
	include/MainWindow.h
	include/PlaylistModel.h
	include/PlaylistView.h
	include/PlaylistViewDelegate.h
	include/VolumeWidget.h)

qt5_add_resources (RES_LIST
	res/SPlay.qrc)

source_group ("Header Files" FILES ${INCLUDE_LIST})
source_group ("Source Files" FILES ${SRC_LIST})
source_group ("Source Files\\MOC" FILES ${MOC_SRC_LIST})
source_group ("Resource Files" FILES ${RES_LIST})

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${EXTERNAL_INCLUDE_DIRS}
	${TAGLIB_INCLUDE_DIRS})

add_executable (${PROJECT_NAME} WIN32 MACOSX_BUNDLE
	${INCLUDE_LIST}
	${SRC_LIST}
	${MOC_SRC_LIST}
	${RES_LIST})

if (NOT WIN32)
	set (UNIX_DEPENDENCY "-lz")
endif ()

target_link_libraries(${PROJECT_NAME}
	${Qt5Core_QTMAIN_LIBRARIES}
	${CMake_QT_LIBRARIES}
	${TAGLIB_LIBRARIES}
	${UNIX_DEPENDENCY})
