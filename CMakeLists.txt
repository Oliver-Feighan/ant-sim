cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)

project(ant_sim)

find_package(SFML COMPONENTS window graphics system REQUIRED)

find_package(Armadillo REQUIRED)

message("-- Armadillo library found")
message("     ARMADILLO_VERSION: " ${ARMADILLO_VERSION_STRING})
message("     ARMADILLO_LIBRARIES   : " ${ARMADILLO_LIBRARIES})
message("     ARMADILLO_INCLUDE_DIRS: " ${ARMADILLO_INCLUDE_DIRS})

include_directories(${SFML_INCLUDE_DIR})
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(ant_sim
	src/main.cpp
	src/ant.cpp
	src/food.cpp
)

target_link_libraries(ant_sim PRIVATE sfml-window)
target_link_libraries(ant_sim PRIVATE sfml-graphics)
target_link_libraries(ant_sim PRIVATE sfml-system)
target_link_libraries(ant_sim PRIVATE ${ARMADILLO_LIBRARIES})
