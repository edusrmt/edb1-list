cmake_minimum_required(VERSION 3.5)
project (List)

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Test target ===

# The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES_TEST "test/*.cpp" )
#file(GLOB SOURCES_TEST "src/*.cpp" )

# Define the sources
set(EXECUTABLE_OUTPUT_PATH "bin")
add_executable(run_tests ${SOURCES_TEST} )
#add_executable(run_drive ${SOURCES_TEST} )