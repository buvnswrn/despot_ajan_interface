cmake_minimum_required(VERSION 3.11)
project(laser_tag)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
  tf
  message_generation
)

find_package(Despot CONFIG REQUIRED)

# Locate Java-related variables
find_package(Java REQUIRED)
include(UseJava)

# Locate JNI
find_package(JNI REQUIRED)
message(STATUS "JNI found at: ${JNI_INCLUDE_DIRS}")

# set the path of the java files
set(JAVA_SOURCE_DIR src/ajan_pomdp_planner/java)
set(JAVA_OUTPUT_DIR src/ajan_pomdp_planner/java)
set(CMAKE_MAVEN_HOME "$ENV{HOME}/.m2/repository")
message(STATUS "Java Source directory: ${JAVA_SOURCE_DIR}")

# set the path of the cpp files
set(CPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
set(CMAKE_CXX_STANDARD 17)

#find the jars
find_jar(COMMONS_CODEC NAMES "commons-codec-1.11" PATHS "${CMAKE_MAVEN_HOME}/commons-codec/commons-codec/1.11")
find_jar(COMMONS_LOG NAMES "commons-logging-1.2" PATHS "${CMAKE_MAVEN_HOME}/commons-logging/commons-logging/1.2")
find_jar(HTTP_CLIENT NAMES "httpclient-4.5.13" PATHS "${CMAKE_MAVEN_HOME}/org/apache/httpcomponents/httpclient/4.5.13")
find_jar(HTTP_CORE NAMES "httpcore-4.4.14" PATHS "${CMAKE_MAVEN_HOME}/org/apache/httpcomponents/httpcore/4.4.14")
find_jar(JSON NAMES "json-20230227" PATHS "${CMAKE_MAVEN_HOME}/org/json/json/20230227")

# Compile Java Sources
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")
file(GLOB_RECURSE JAVA_SOURCE_FILES "${JAVA_SOURCE_DIR}/*.java")
file(GLOB_RECURSE CMAKE_MAVEN_JARS "${CMAKE_MAVEN_HOME}/*.jar")
add_jar(ajan_jar SOURCES ${JAVA_SOURCE_FILES} INCLUDE_JARS ${CMAKE_MAVEN_JARS} GENERATE_NATIVE_HEADERS ajan_jni DESTINATION include/ajan_jni_headers)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS thread)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  YoubotActionObs.srv
  TagActionObs.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

###########
## Build ##
###########

include_directories(
      ${catkin_INCLUDE_DIRS}
      ${Boost_INCLUDE_DIRS}
      ${JNI_INCLUDE_DIRS}
      include/robot_controller
      include/unified_pomdp_planner
      include/ajan_pomdp_planner
      include/ajan_jni_headers
)

## Declare a C++ executable
add_executable(youbot_interface src/robot_controller/youbot_interface.cpp)
add_dependencies(youbot_interface ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(youbot_interface ${catkin_LIBRARIES})

## Declare a C++ executable
add_executable(laser_tag_controller src/robot_controller/laser_tag_controller.cpp)
add_dependencies(laser_tag_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(laser_tag_controller ${catkin_LIBRARIES})


## Declare a C++ executable
add_executable(unified_pomdp_planner src/unified_pomdp_planner/unified_laser_tag.cpp src/unified_pomdp_planner/unified_laser_tag_world.cpp src/unified_pomdp_planner/main.cpp src/unified_pomdp_planner/tag_belief.cpp src/unified_pomdp_planner/tag_belief.cpp src/unified_pomdp_planner/tag_state.cpp src/unified_pomdp_planner/tag_state.cpp src/unified_pomdp_planner/tag_shr_policy.cpp src/unified_pomdp_planner/tag_shr_policy.cpp src/unified_pomdp_planner/tag_manhattan_upperbound.cpp src/unified_pomdp_planner/tag_sp_particleupperbound.cpp src/unified_pomdp_planner/tag_blind_beliefpolicy.cpp)
add_dependencies(unified_pomdp_planner ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(unified_pomdp_planner despot ${catkin_LIBRARIES})

## Declare a C++ executable
add_executable(ajan_pomdp_planner src/ajan_pomdp_planner src/ajan_pomdp_planner/cpp/ajan_belief.cpp src/ajan_pomdp_planner/cpp/ajan_state.cpp src/ajan_pomdp_planner/cpp/ajan_agent.cpp src/ajan_pomdp_planner/cpp/ajan_beliefpolicy.cpp src/ajan_pomdp_planner/cpp/ajan_world.cpp src/ajan_pomdp_planner/cpp/ajan_policy.cpp src/ajan_pomdp_planner/cpp/ajan_upperbound.cpp src/ajan_pomdp_planner/cpp/ajan_particleupperbound.cpp src/ajan_pomdp_planner/cpp/ajan_helper.cpp src/ajan_pomdp_planner/cpp/ajan_helper.h)
add_dependencies(ajan_pomdp_planner ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ajan_pomdp_planner despot ${catkin_LIBRARIES})

## Declare a C++ Library
file(GLOB_RECURSE CPP_SOURCE_FILES "src/ajan_pomdp_planner/cpp/*.cpp")
add_library(ajan_planner SHARED ${CPP_SOURCE_FILES})
target_link_libraries(ajan_planner despot ${catkin_LIBRARIES})
# Link the JNI library
target_include_directories(ajan_planner PRIVATE ${JNI_INCLUDE_DIRS})
set_target_properties(ajan_planner PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/jniLibs")

#############
## Testing ##
#############
add_executable(test_laser_tag_controller test/test_laser_tag_controller.cpp)
add_dependencies(test_laser_tag_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_laser_tag_controller ${catkin_LIBRARIES})


