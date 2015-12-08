cmake_minimum_required(VERSION 2.8)
enable_testing()
set(PROJECT_NAME mrl)
project(${PROJECT_NAME} C)
include_directories(.)

set(here ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(mrl)
#add_subdirectory(apps)
