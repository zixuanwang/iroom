PROJECT(iroom)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -g -O0 -std=c++11")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(CURL REQUIRED)

INCLUDE_DIRECTORIES(
${OPENCV_INCLUDE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}
${Boost_INCLUDE_DIRS}
${CURL_INCLUDE_DIR}
)
ADD_EXECUTABLE(iroom Camera.h Camera.cpp Room.h Room.cpp main.cpp)
TARGET_LINK_LIBRARIES(iroom ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
