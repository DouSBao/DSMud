#!/bin/zsh

local CMAKE_FLAGS=""
local CMAKE_SRC_DIR="."
local CMAKE_BUILD_DIR="build"

function help()
{
	echo "build.sh is a cmake driven used to build DSMud."
	echo "only out source build is avaiable"
	echo "\tavaiable options:"
	echo "\t\t\e[33m[default]\e[0m : build and install."
	echo "\t\t\e[33m-b|--build\e[0m : build without install."
	echo "\t\t\e[33m-r|--rebuild\e[0m : (re)build cache."
	echo "\t\t\e[33m-i|--install\e[0m : install."
	echo "\t\t\e[33m-h|--help\e[0m : print help information."
}

function healthcheck()
{
	[ $(basename $PWD) = "DSMud" ] && return 0 || (echo "\e[31m[FAIL]\e[0m build.sh must be executed under root directory of DSMud" && exit -1)
}

function build_cache()
{
	cmake -S ${CMAKE_SRC_DIR} -B ${CMAKE_BUILD_DIR} ${CMAKE_FLAGS}
}

function rebuild_cache()
{
	cmake --fresh -S ${CMAKE_SRC_DIR} -B ${CMAKE_BUILD_DIR} ${CMAKE_FLAGS}
}

function build_project()
{
	cmake --build ${CMAKE_BUILD_DIR}
}

function install_project()
{
	cmake --build ${CMAKE_BUILD_DIR} --target install
}

healthcheck

case $1 in
"-b"|"--build")
	build_cache && build_project;;
"-r"|"--rebuild")
	rebuild_cache;;
"-i"|"--install")
	install_project;;
"-h"|"--help")
	help;;
*)
	build_cache && install_project;;
esac
