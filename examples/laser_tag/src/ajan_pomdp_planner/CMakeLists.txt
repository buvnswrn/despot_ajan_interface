cmake_minimum_required(VERSION 2.8.3)
project(laser_tag)

# Locate Java-related variables
find_package(Java REQUIRED)
include(UseJava)

# Locate JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(Despot CONFIG REQUIRED)

# set the path of the java files
set(JAVA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/java)
set(JAVA_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/java)
message(STATUS "Java Source directory: ${JAVA_SOURCE_DIR}")

# set the path of the cpp files
set(CPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
set(CMAKE_CXX_STANDARD 17)

# Compile Java Sources
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")
file(GLOB_RECURSE JAVA_SOURCE_FILES "${JAVA_SOURCE_DIR}/*.java")
add_jar(AjanDespotJar ${JAVA_SOURCE_FILES} OUTPUT_DIR ${JAVA_OUTPUT_DIR})

# Compile C++ sources into a shared library
file(GLOB_RECURSE CPP_SOURCE_FILES "${CPP_SOURCE_DIR}/*.cpp")
add_library(AjanDespot SHARED ${CPP_SOURCE_FILES})

# Link the JNI library
target_include_directories(AjanDespot PRIVATE ${JNI_INCLUDE_DIRS})

# set the output directory for the shared library
set_target_properties(AjanDespot PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/jniLibs/")

