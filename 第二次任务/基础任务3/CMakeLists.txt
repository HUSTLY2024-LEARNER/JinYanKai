cmake_minimum_required(VERSION 3.10)
project(task3)
set(CMAKE_CXX_STANDARD 11)


find_package(OpenCV 4 REQUIRED)

add_executable(task3 mission3.cpp)
target_include_directories(task3 BEFORE
	PUBLIC ${OpenCV_DIRS}
)

target_link_libraries(task3
	PUBLIC ${OpenCV_LIBS}
)
