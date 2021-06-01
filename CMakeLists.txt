cmake_minimum_required(VERSION 3.0.2)
project(pointcloud_practice)

find_package(
  catkin REQUIRED
  roscpp
  sensor_msgs
  pcl_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES velodyne_record
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(passThrough src/passThrough.cpp)
add_executable(voxelization src/voxelization.cpp)
add_executable(statisticalFilter src/statisticalFilter.cpp)
add_executable(radiusFilter src/radiusFilter.cpp)
add_executable(euclideanCluster src/euclideanCluster.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(passThrough ${catkin_EXPORTED_TARGETS})
add_dependencies(voxelization ${catkin_EXPORTED_TARGETS})
add_dependencies(statisticalFilter ${catkin_EXPORTED_TARGETS})
add_dependencies(radiusFilter ${catkin_EXPORTED_TARGETS})
add_dependencies(euclideanCluster ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(passThrough ${catkin_LIBRARIES})
target_link_libraries(voxelization ${catkin_LIBRARIES})
target_link_libraries(statisticalFilter ${catkin_LIBRARIES})
target_link_libraries(radiusFilter ${catkin_LIBRARIES})
target_link_libraries(euclideanCluster ${catkin_LIBRARIES})


#############
## Install ##
#############

install(DIRECTORY
    launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

