PROJECT(iroom)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -g -O0 -std=c++11")

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(CURL REQUIRED)

INCLUDE_DIRECTORIES(
${OPENCV_INCLUDE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}
${Boost_INCLUDE_DIRS}
${CURL_INCLUDE_DIR}
)
ADD_EXECUTABLE(analyser AnalyserMain.cpp FeatureDescriptor.h FeatureDescriptor.cpp Histogram.h Histogram.cpp ColorDescriptor.h ColorDescriptor.cpp HoGDescriptor.h HoGDescriptor.cpp MotionDescriptor.h MotionDescriptor.cpp Utility.h Utility.cpp)
ADD_EXECUTABLE(camera Camera.h Camera.cpp CameraMain.cpp)
ADD_EXECUTABLE(iroom iRoomMain.cpp)
ADD_EXECUTABLE(annotate AnnotateMain.cpp)
TARGET_LINK_LIBRARIES(camera ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
TARGET_LINK_LIBRARIES(analyser ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(annotate ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})
