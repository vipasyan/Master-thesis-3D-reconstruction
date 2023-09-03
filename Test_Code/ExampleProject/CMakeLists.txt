#
# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
# Author: Sascha Brandt <sascha@brandt.graphics>
#

# required by CMake
cmake_minimum_required(VERSION 3.1.0)

# set the project name to the name of the current folder
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# ensures that the project is build with C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add C++ source files to the project
add_library(${PROJECT_NAME} SHARED
	src/Main.cpp
	src/ELibExamples.cpp
	src/ExampleRenderer/ExampleRenderer.cpp
	src/ExampleRenderer/E_ExampleRenderer.cpp
	# add your own .cpp files here
)

# pass the project name to the Main.cpp file in form of the define 'LIBRARY_NAME'
set_source_files_properties(src/Main.cpp PROPERTIES COMPILE_DEFINITIONS LIBRARY_NAME="${PROJECT_NAME}")

# make sure that the built .dll or .so file is placed into the 'build' or 'bin' directory
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# defines dllexport macro required by windows dll's, e.g., EXAMPLEPROJECTAPI
string(TOUPPER "${PROJECT_NAME}API" PROJECT_API)
if(MSVC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
	target_compile_definitions(${PROJECT_NAME} PRIVATE "${PROJECT_API}=__declspec(dllexport)")
	target_compile_definitions(${PROJECT_NAME} INTERFACE "${PROJECT_API}=__declspec(dllimport)")
else()
	target_compile_definitions(${PROJECT_NAME} PRIVATE "${PROJECT_API}=")
	target_compile_definitions(${PROJECT_NAME} INTERFACE "${PROJECT_API}=")
endif()

# EXAMPLEPROJECTAPI alias for main file
set_property(SOURCE src/Main.cpp APPEND PROPERTY COMPILE_DEFINITIONS LIBRARY_API=${PROJECT_API})

# --- Set up dependencies to the PADrend libraries ---

# add ./cmake to module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# find PADrend libraries
find_package(PADrend)
if(PADREND_FOUND)
	target_link_libraries(${PROJECT_NAME} PRIVATE PADrend::PADrend)
endif()

# find EScript library
find_package(EScript)
if(ESCRIPT_FOUND)
	target_link_libraries(${PROJECT_NAME} PRIVATE EScript::EScript)
endif()

# --- Optional dependencies ---

# Dependency to PACKAGE
#find_package(PACKAGE)
#if(PACKAGE_FOUND)
#	 target_include_directories(${PROJECT_NAME} PRIVATE ${PACKAGE_INCLUDE_DIRS})
#	 target_link_libraries(${PROJECT_NAME} LINK_PRIVATE ${PACKAGE_LIBRARIES})
#	 target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_LIB_PACKAGE)
#endif()
