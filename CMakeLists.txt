cmake_minimum_required(VERSION 2.8.4)
project(SGM)

#set(CMAKE_CXX_STANDARD 11)
#add_definitions(-std=c++11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
if(POLICY CMP0046)
  cmake_policy(SET CMP0046 NEW)
endif()
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(./)

add_library(sgm STATIC 
##    ./AD_postProcess.cpp
    ./cost.cpp
    ./dp.cpp
    ./image.cpp
    ./post_processing.cpp
    ./prefilter.cpp
    ./select_disp.cpp
)

add_executable(demo main.cpp)
target_link_libraries(demo sgm ${OpenCV_LIBS})
