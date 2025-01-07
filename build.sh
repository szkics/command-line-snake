#!/bin/bash
# TODO: change to current directory.
set -e
SCRIPT_PATH=`readlink -f $0`
SRC_ROOT=`dirname $SCRIPT_PATH`
if [ $# -eq 0 ]
then
	export CXXFLAGS="-Wall -march=native -Wunused-parameter -fPIC"

	# Absolute path this script is in. eg: /home/user/bin
	cd $SRC_ROOT
	mkdir -p build
	cd build
	pwd
	cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=$BUILD_ROOT/deploy
	make .
	make tests_snake
	./tests_snake
elif [ "$1" == "-c" ] || [ "$1" == "--coverage" ]
then
	# coverage
	cd $SRC_ROOT
	kcov --include-path=/home/developer/projects/calib-ansic-internal/snake/ --exclude-path=/home/developer/projects/calib-ansic-internal/snake/catch/,/home/developer/projects/calib-ansic-internal/snake/fakeit/,/home/developer/projects/calib-ansic-internal/snake/dependencies/,/home/developer/projects/calib-ansic-internal/snake/UnitTest/ kcov_result/ build/tests_snake
	firefox kcov_result/index.html
elif [ "$1" == "--gcovr" ]
then
	# clean
	cd $SRC_ROOT
	dirname=$(find . -type d -name 'build')
	if [ "$dirname" = "./build" ]
	then
		rm -r ./build
	fi
	dirname=$(find . -type d -name 'kcov_result')
	if [ "$dirname" = "./kcov_result" ]
	then
		rm -r ./kcov_result
	fi

	# set compiler flags to include -fprofile-arcs
	export CXXFLAGS="-Wall -march=native -Wunused-parameter -fPIC -ftest-coverage -fprofile-arcs"

	# run tests
	cd $SRC_ROOT
	mkdir -p build
	cd build
	pwd
	cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=$BUILD_ROOT/deploy
	make .
	make tests_snake
	./tests_snake
	
	# calc coverage	
	cd ..
	gcovr -r . --html --html-details -e UnitTest/* -e catch/* -e dependencies/kbhit.cpp -e headers/headers.h -e menu/menu.cpp -e timer/timer.cpp -e userinteraction/userinteraction.cpp -e fakeit/fakeit.hpp -e  build/CMakeFiles/3.15.3/CompilerIdCXX/CMakeCXXCompilerId.cpp -o example-html-details.html
	firefox example-html-details.html
elif [ "$1" == "--clean" ]
then
	cd $SRC_ROOT
	dirname=$(find . -type d -name 'build')
	if [ "$dirname" = "./build" ]
	then
		rm -r ./build
	fi
	dirname=$(find . -type d -name 'kcov_result')
	if [ "$dirname" = "./kcov_result" ]
	then
		rm -r ./kcov_result
	fi
elif [ "$1" == "-g" ] || [ "$1" == "--game" ]
then
	cd $SRC_ROOT	
	echo "stty -g $(stty -g)" > restore-sanity
	stty cbreak
	g++ -c start.cpp
	g++ -c snake/snake.cpp
	g++ -c menu/menu.cpp
	g++ -c gamemodes/gamemodes.cpp
	g++ -c entities/entities.cpp
	g++ -c gamelogic/gamelogic.cpp
	g++ -c timer/timer.cpp
	g++ -c userinteraction/userinteraction.cpp	
	g++ -c dependencies/kbhit.cpp
	g++ -std=c++11 -pthread -lpthread start.o snake.o menu.o gamemodes.o entities.o gamelogic.o timer.o userinteraction.o kbhit.o
	./a.out
	/bin/stty cooked
	rm restore-sanity
	rm a.out
elif [ "$1" == "-h" ]
then
	cd $SRC_ROOT
	echo "usage:  ./build.sh (by default, for running all unit tests)"
	echo "	./build.sh -game (for playing the actual snake game)"
	echo "	./build.sh --clean (removing build directory)"
	echo "	./build.sh -c (for coverage with kcov)"	
	echo "	./build.sh --gcovr (for coverage with gcovr)"	
else
	cd $SRC_ROOT
	echo "for usage: ./build.sh -h"
fi