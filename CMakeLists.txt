cmake_minimum_required(VERSION 3.2)
project(learncpp)

set(SOURCES
    src/book.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(include)
