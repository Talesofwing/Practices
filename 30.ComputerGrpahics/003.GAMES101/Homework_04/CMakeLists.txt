cmake_minimum_required(VERSION 3.10)
project(BezierCurve)

# Add eigen & opencv include path
include_directories(
	${CMAKE_SOURCE_DIR}/../3rdparty
	${CMAKE_SOURCE_DIR}/../3rdparty/opencv/include
)

# Link eigen & opencv lib
link_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv/lib)

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve PRIVATE opencv_core4120 opencv_imgproc4120 opencv_highgui4120 opencv_imgcodecs4120)
