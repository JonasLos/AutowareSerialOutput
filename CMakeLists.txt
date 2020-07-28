cmake_minimum_required(VERSION 2.8.3)
project(mava_interface)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  autoware_msgs
)

catkin_package(
  CATKIN_DEPENDS
    serial
    std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(mava_interface src/mava_interface.cpp)

target_link_libraries(mava_interface
  ${catkin_LIBRARIES}
)
