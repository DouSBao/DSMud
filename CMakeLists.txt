cmake_minimum_required(VERSION 3.0)
project(DSMud LANGUAGE CXX)

# language setting
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build settings
set(BUILD_SHARED_LIBS ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
