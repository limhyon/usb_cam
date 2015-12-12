# sudo apt-get install libavcodec-dev
cmake_minimum_required(VERSION 2.8.3)
project(usb_cam)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(catkin REQUIRED COMPONENTS image_transport roscpp std_msgs sensor_msgs camera_info_manager)

## pkg-config libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(avcodec libavcodec REQUIRED)
pkg_check_modules(avformat libavformat REQUIRED)
pkg_check_modules(swscale libswscale REQUIRED)
pkg_check_modules(avutil libavutil REQUIRED)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_VERBOSE_MAKEFILE yes)

###################################################
## Declare things to be passed to other projects ##
###################################################

## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ${PROJECT_NAME}
#)

###########
## Build ##
###########

include_directories(include
  ${swscale_INCLUDE_DIRS}
  ${avcodec_INCLUDE_DIRS}
  ${avformat_INCLUDE_DIRS}
  ${avutil_INCLUDE_DIRS}
)

## Build the USB camera library
add_library(${PROJECT_NAME} src/usb_cam.cpp)
target_link_libraries(${PROJECT_NAME})

## Declare a cpp executable
add_executable(${PROJECT_NAME}_test examples/usb_cam_test.cc)
target_link_libraries(${PROJECT_NAME}_test
  ${PROJECT_NAME}
  ${swscale_LIBRARIES}
  ${avcodec_LIBRARIES}
  ${avutil_LIBRARIES}
  ${avformat_LIBRARIES}
)
