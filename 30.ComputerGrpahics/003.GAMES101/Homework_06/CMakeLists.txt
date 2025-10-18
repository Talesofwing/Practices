cmake_minimum_required(VERSION 3.10)
project(Raytracing)

# Add eigen & opencv include path
include_directories(
	${CMAKE_SOURCE_DIR}/../3rdparty
	${CMAKE_SOURCE_DIR}/../3rdparty/opencv/include
)

# Link eigen & opencv lib
link_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv/lib)

add_executable(Raytracing
	main.cpp Renderer.cpp Scene.cpp BVH.cpp Vector.cpp
)

target_link_libraries(Raytracing PRIVATE opencv_core4120 opencv_imgproc4120 opencv_highgui4120 opencv_imgcodecs4120)
