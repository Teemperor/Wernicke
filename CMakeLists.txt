cmake_minimum_required(VERSION 3.3)
project(wernicke)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

configure_file(gnuplot.gp ${CMAKE_CURRENT_BINARY_DIR}/gnuplot.gp COPYONLY)


add_subdirectory(ui)
add_subdirectory(lib)