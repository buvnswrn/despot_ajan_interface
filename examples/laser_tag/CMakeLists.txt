cmake_minimum_required(VERSION 2.8.3)
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
  include/robot_controller
  include/pomdp_planner
  include/unified_pomdp_planner
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

#############
## Testing ##
#############
add_executable(test_laser_tag_controller test/test_laser_tag_controller.cpp)
add_dependencies(test_laser_tag_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_laser_tag_controller ${catkin_LIBRARIES})


