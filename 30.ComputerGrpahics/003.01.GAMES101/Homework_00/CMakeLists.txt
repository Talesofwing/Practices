cmake_minimum_required(VERSION 3.10)
project(Transformation)

# Add eigen & opencv include path
include_directories(
	${CMAKE_SOURCE_DIR}/../3rdparty
	${CMAKE_SOURCE_DIR}/../3rdparty/opencv/include
)

# Link eigen & opencv lib
link_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv/lib)

add_executable(Transformation main.cpp)

target_link_libraries(Transformation)
