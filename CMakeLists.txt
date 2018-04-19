cmake_minimum_required(VERSION 2.8.3)
project(phidgets_project)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  joy_controller
)


catkin_package(
  #INCLUDE_DIRS include
  #LIBRARIES phidgets_project 
  #CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  #DEPENDS system_lib
)


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


add_executable(motor_c src/collect_data.cpp)
target_link_libraries(motor_c ${catkin_LIBRARIES})



