cmake_minimum_required(VERSION 2.8)

project(STest)

set(INCLUDE_LIST
	include/Aux.h)

set(SRC_LIST
	src/Aux.cpp
	src/main.cpp)

#source_group("Header Files" FILES ${INCLUDE_LIST})
#source_group("Source Files" FILES ${SRC_LIST})

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
	${INCLUDE_LIST}
	${SRC_LIST})

