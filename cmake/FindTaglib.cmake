# This module finds the taglib library.
#
# Usage:
#	find_package(Taglib)
#
# On completion, the script defines the following variables:
#	
#		- Compound variables:
#   taglib_found 
#		- true if all requested components were found.
#	taglib_libraries 
#		- contains release (and debug if available) libraries for all
#		  requested components.
#		  It has the form "optimized LIB1 debug LIBd1 optimized LIB2 ...",
#		  ready for use with the target_link_libraries command.
#	taglib_include_dirs
#		- Contains include directory for all requested components.

if (NOT taglib_root)
	set(taglib_root $ENV{taglib_root})
endif()

set(taglib_include_dirs
	${taglib_root}/taglib
	${taglib_root}/taglib/toolkit
	${taglib_root}/taglib/ape
	${taglib_root}/taglib/mpeg
	${taglib_root}/taglib/mpeg/id3v1
	${taglib_root}/taglib/mpeg/id3v2
	${taglib_root}/bindings/c/)

if (WIN32)
	set(taglib_lib_name "tag.lib")
else ()
	set(taglib_lib_name "libtag.a")
endif ()

if (CMAKE_CL_64)
	set(taglib_lib_path ${taglib_root}/lib/x64)
else ()
	set(taglib_lib_path ${taglib_root}/lib/x32)
endif()

find_library(
	taglib_debug_lib
	NAMES
		${taglib_lib_name}
	PATHS
		${taglib_lib_path}/Debug
)

if (NOT taglib_debug_lib)
		message(FATAL_ERROR "${taglib_lib_name} for debug not found in ${taglib_lib_path}")
endif ()

find_library(
	taglib_release_lib
	NAMES
		${taglib_lib_name}
	PATHS
		${taglib_lib_path}/Release
)

if (NOT taglib_release_lib)
		message(FATAL_ERROR "${taglib_lib_name} for release not found in ${taglib_lib_path}")
endif ()

list(APPEND taglib_libraries "optimized" ${taglib_release_lib})

if (taglib_debug_lib)
	list(APPEND taglib_libraries "debug" ${taglib_debug_lib})
endif ()

mark_as_advanced(taglib_libraries)

# Support the REQUIRED and QUIET arguments, and set CRYPTOPP_FOUND if found.

if (DEFINED taglib_libraries)
	set(taglib_found TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(taglib REQUIRED_VARS taglib_root)
