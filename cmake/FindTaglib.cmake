# This module finds the taglib library.
#
# Usage:
#	find_package(Taglib)
#
# On completion, the script defines the following variables:
#
#	TAGLIB_FOUND
#		- true if all requested components were found.
#	TAGLIB_LIBRARIES
#		- contains release (and debug if available) libraries for all
#		  requested components. It has the form
#		  "optimized LIB1 debug LIBd1 optimized LIB2 ...",
#		  ready for use with the target_link_libraries command.
#	TAGLIB_INCLUDE_DIRS
#		- Contains include directory for all requested components.
#	TAGLIB_VERSION
#		- Current library version.

if (WIN32)
	set (TAGLIB_ROOT "C:/Program Files/taglib")
	set (TAGLIB_CONFIG_UTIL_NAME "taglib-config.cmd")
elseif (UNIX OR APPLE)
	set (TAGLIB_ROOT "/usr/local")
	set (TAGLIB_CONFIG_UTIL_NAME "taglib-config")
endif ()

find_program (TAGLIBCONFIG_EXECUTABLE
	NAMES ${TAGLIB_CONFIG_UTIL_NAME} PATHS ${TAGLIB_ROOT}/bin)

if (TAGLIBCONFIG_EXECUTABLE)
	exec_program (${TAGLIBCONFIG_EXECUTABLE}
		ARGS --version OUTPUT_VARIABLE TAGLIB_VERSION)
endif ()

set (TAGLIB_INCLUDE_DIRS ${TAGLIB_ROOT}/include)
message (STATUS "Taglib includes ${TAGLIB_INCLUDE_DIRS}")

if (WIN32)
	if (CMAKE_CL_64)
		set (TAGLIB_LIB_PATH "${TAGLIB_ROOT}/lib/x64")
	else ()
		set (TAGLIB_LIB_PATH "${TAGLIB_ROOT}/lib/x32")
	endif ()
	set (TAGLIB_LIB_NAME "tag.lib")
elseif (UNIX OR APPLE)
	set (TAGLIB_LIB_PATH "${TAGLIB_ROOT}/lib/taglib")
	set (TAGLIB_LIB_NAME "libtag.a")
endif ()

find_library (TAGLIB_DEBUG_LIB
	NAMES ${TAGLIB_LIB_NAME} PATHS ${TAGLIB_LIB_PATH}/debug)

if (NOT TAGLIB_DEBUG_LIB)
	message (WARNING
		"${TAGLIB_LIB_NAME} for debug not found in ${TAGLIB_LIB_PATH}/debug")
endif ()

find_library (TAGLIB_RELEASE_LIB
	NAMES ${TAGLIB_LIB_NAME} PATHS ${TAGLIB_LIB_PATH}/release)

if (NOT TAGLIB_RELEASE_LIB)
	message(WARNING
		"${TAGLIB_LIB_NAME} for release not found in ${TAGLIB_LIB_PATH}/release")
endif ()

list(APPEND TAGLIB_LIBRARIES "optimized" ${TAGLIB_RELEASE_LIB})

if (TAGLIB_DEBUG_LIB)
	list (APPEND TAGLIB_LIBRARIES "debug" ${TAGLIB_DEBUG_LIB})
endif ()

mark_as_advanced(TAGLIB_LIBRARIES)
message (STATUS "Taglib libraries ${TAGLIB_LIBRARIES}")

if (DEFINED TAGLIB_LIBRARIES)
	set (TAGLIB_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Taglib
	REQUIRED_VARS TAGLIB_ROOT VERSION_VAR TAGLIB_VERSION)
