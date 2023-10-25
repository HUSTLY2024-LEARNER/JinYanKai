cmake_minimum_required(VERSION 3.10)
project(task1)
set(CMAKE_CXX_STANDARD 11)


find_package(OpenCV 4 REQUIRED)

add_executable(task1 atmethod.cpp)
target_include_directories(task1 BEFORE
	PUBLIC ${OpenCV_DIRS}
)

target_link_libraries(task1
	PUBLIC ${OpenCV_LIBS}
)
