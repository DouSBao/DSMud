#!/bin/zsh

local CMAKE_FLAG=""
local CMAKE_SRC_DIR="."
local CMAKE_BUILD_DIR="build"

function help()
{
	echo "build.sh is a cmake driven used to build DSMud."
	echo "\tavaiable option:"
	echo "\t\t\e[33m[default]\e[0m : build project."
	echo "\t\t\e[33m-r|--rebuild\e[0m : rebuild cmake cache."
	echo "\t\t\e[33m-h|--help\e[0m : print help information."
}

function healthcheck()
{
	[ $(basename $PWD) = "DSMud" ] && return 0 || (echo "\e[31m[FAIL]\e[0m build.sh must be executed under root directory of DSMud" && exit -1)
}

function build()
{
	cmake $CMAKE_FLAG -H${CMAKE_SRC_DIR} -B${CMAKE_BUILD_DIR}
}

function rebuild()
{
	cmake $CMAKE_FLAG --fresh${CMAKE_SRC_DIR} -H${CMAKE_SRC_DIR} -B${CMAKE_BUILD_DIR}
}

case $1 in
"-h"|"--help")
	help;;
"-r"|"--rebuild")
	healthcheck && rebuild;;
*)
	healthcheck && build;;
esac
