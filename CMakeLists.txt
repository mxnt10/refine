cmake_minimum_required(VERSION 3.19)
project(refn)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -O2)

set(REFN_SOURCES
	main.cpp
	main.h
	utils/control_utils.cpp
	utils/control_utils.h
	utils/err_msg.cpp
	utils/err_msg.h
	utils/file_utils.cpp
	utils/file_utils.h
	utils/line_utils.cpp
	utils/line_utils.h
	utils/parm.h
)

add_executable(refn ${REFN_SOURCES})
