cmake_minimum_required(VERSION 3.0.2)
project(pointcloud_practice)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  pcl_ros
)

catkin_package(

)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  #include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(voxelization src/voxelization.cpp)
add_executable(filter src/filter.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(
   voxelization
   ${catkin_EXPORTED_TARGETS}
)
add_dependencies(
   filter
   ${catkin_EXPORTED_TARGETS}
)

## Specify libraries to link a library or executable target against
target_link_libraries(
   voxelization
   ${catkin_LIBRARIES}
)
target_link_libraries(
   filter
   ${catkin_LIBRARIES}
)
