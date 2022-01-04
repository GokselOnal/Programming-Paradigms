cmake_minimum_required(VERSION 3.5)

project(week14 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("range-v3/include")


add_executable(week14 main.cpp)
