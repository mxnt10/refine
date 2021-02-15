cmake_minimum_required(VERSION 3.17)
project(refine)

set(CMAKE_CXX_STANDARD 20)

add_executable(refine main.cpp utils/control_utils.h utils/file_utils.h utils/line_utils.h)
