cmake_minimum_required(VERSION 3.0.0)
project(Pham VERSION 0.1.0)


file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)


add_library(Pham ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

