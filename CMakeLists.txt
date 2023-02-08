cmake_minimum_required(VERSION 3.15)
project(DSMud)

# options
option(USRDEF_BUILD_STATIC_VERSION "Build static executable and libraries" ON)

# language setting
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build settings
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_IN_SOURCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# advanced settings
set(DEV_BUILD_DEBUG OFF CACHE STRING "Build subdirectory debug")

mark_as_advanced(DEV_BUILD_DEBUG)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# project cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/etc/cmake")

# modules used
include(ExportHeaders)

# clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# build messages
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install path: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Library output directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "Archive output directory: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# build
add_subdirectory(src)

if(DEV_BUILD_DEBUG)
	add_subdirectory(debug)
endif()
