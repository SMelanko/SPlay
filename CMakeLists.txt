cmake_minimum_required(VERSION 2.8)

project(stest)

aux_source_directory(include INC_LIST)
aux_source_directory(src SRC_LIST)

add_executable(${PROJECT_NAME}
	${INC_LIST}
    ${SRC_LIST})
