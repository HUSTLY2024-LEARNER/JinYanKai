cmake_minimum_required(VERSION 3.10)
project(task2)
set(CMAKE_CXX_STANDARD 11)


find_package(OpenCV 4 REQUIRED)

add_executable(task2 mission2.cpp)
target_include_directories(task2 BEFORE
	PUBLIC ${OpenCV_DIRS}
)

target_link_libraries(task2
	PUBLIC ${OpenCV_LIBS}
)
