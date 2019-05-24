cmake_minimum_required(VERSION 2.8.3)
project(watrix_vp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs geometry_msgs geodesy geographic_msgs nav_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  geodesy
  roscpp
  rospy
  std_msgs
)


add_message_files(FILES
  GPS_IMU.msg
  #my_lidar_msg.msg
)
generate_messages(DEPENDENCIES
  std_msgs
)



catkin_package(
  CATKIN_DEPENDS
  message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES watrix_vp
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
# ${catkin_INCLUDE_DIRS}
)




add_executable(gnss_node
  src/gnss_node.cpp
)
add_dependencies(gnss_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(gnss_node
  ${catkin_LIBRARIES}
)

add_executable(lidar_node
  src/lidar_node.cpp
)
add_dependencies(lidar_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(lidar_node
  ${catkin_LIBRARIES}
)
