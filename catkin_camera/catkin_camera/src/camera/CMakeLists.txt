cmake_minimum_required(VERSION 3.0.2)
project(camera)
set(OpenCV_DIR /usr/share/OpenCV/)
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  OpenCV
  geometry_msgs
  roscpp
  sensor_msgs
  cv_bridge
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES camera_to_depth
#  CATKIN_DEPENDS OpenCV geometry_msgs roscpp sensor_msgs
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
add_executable(${PROJECT_NAME} src/camera.cpp)
target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}  #${OpenCV_LIBS}
)
