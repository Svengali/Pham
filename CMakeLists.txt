cmake_minimum_required(VERSION 3.0.0)

include(${CMAKE_TOOLS_DIR}/Macros.cmake)

project(Pham VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add_subdirectory(../cblib)



if (MSVC)
    # For precompiled header.
    # Set 
    # "Precompiled Header" to "Use (/Yu)"
    # "Precompiled Header File" to "stdafx.h"
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
endif()


file(
  GLOB_RECURSE PHAM_HEADERS 
  #LIST_DIRECTORIES true
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.h
)

file(
  GLOB_RECURSE PHAM_SRC
  #LIST_DIRECTORIES true
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
)

GenerateSourceGroups(src)


#ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "src/stdafx.cpp" PHAM_SRC)

set_source_files_properties(src/stdafx.cpp
    PROPERTIES
    COMPILE_FLAGS "/Ycstdafx.h"
)

message("PHAM_HEADERS: ${PHAM_HEADERS}")

message("PHAM_SRC: ${PHAM_SRC}")


add_library(Pham ${PHAM_SRC} ${PHAM_HEADERS})

target_include_directories(Pham PUBLIC ..)
target_link_libraries(Pham cblib enkiTS)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

