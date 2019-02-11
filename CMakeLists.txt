cmake_minimum_required(VERSION 2.8)

project (hwlib)
set(CMAKE_BUILD_TYPE Release)

add_library(hwlib INTERFACE)
target_include_directories(hwlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_sources(hwlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/library/hwlib.cpp)
