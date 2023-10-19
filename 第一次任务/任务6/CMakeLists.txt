cmake_minimum_required(VERSION 3.10)
project(segment_main)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4 REQUIRED)

#include_directories(segment.hpp  opencv.hpp)
#set(SOURCE_FILES src/main.cpp src/segment.cpp )

# main executable
add_executable(main main.cpp segment.h segment.cpp)
target_link_libraries(main 
	PUBLIC ${OpenCV_LIBS}
)

# add_library A

# target_link_libraries A <- PUBLIC B, PRIVATE C

# add_executable D

# D <- A
# target_link_libraries D <- A, C
