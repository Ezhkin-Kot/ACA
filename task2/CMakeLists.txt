cmake_minimum_required(VERSION 3.15)

project(task2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  main.cpp
  heap_sort.cpp
  merge_sort.cpp
  quick_sort.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

