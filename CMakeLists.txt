cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)

project(ant_sim)

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(ant_sim

	src/main.cpp
	src/ant.cpp
)

target_link_libraries(ant_sim PRIVATE sfml-graphics)
