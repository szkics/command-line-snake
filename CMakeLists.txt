cmake_minimum_required(VERSION 3.4.0)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
    "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif ()

project(cmake_test)

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem regex) 
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    include_directories(${CMAKE_SOURCE_DIR}/dependencies) 

	# Prepare "Catch" library for other executables
	set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)

	add_compile_options(-Wall -Wextra -Wpedantic)
	add_compile_options(-fsanitize=thread)
	add_link_options(-fsanitize=thread)
	add_link_options(-lasan)

	add_library(Catch INTERFACE)
	target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

	add_subdirectory(dependencies)
	add_subdirectory(headers)
	add_subdirectory(entities)
	add_subdirectory(gamelogic)
	add_subdirectory(gamemodes)
	add_subdirectory(menu)
	add_subdirectory(snake)

	# Make Unit tests executable
	# testing order manager
	set(TEST_SOURCES_SNAKE ${CMAKE_CURRENT_SOURCE_DIR}/UnitTest/tests_catch2.cpp)
	add_executable(tests_snake ${TEST_SOURCES_SNAKE})
	target_link_libraries(tests_snake
		Catch
		pthread
		dependencies
		headers
		gamelogic
		entities
		gamemodes
		menu
		snake
		${Boost_LIBRARIES})
endif()