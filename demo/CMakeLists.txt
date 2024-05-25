cmake_minimum_required(VERSION 3.8)

project(GameEngine)

include_directories(${CMAKE_SOURCE_DIR}/include/Generic)

add_executable(Demo main.cpp)

target_link_directories(Demo PRIVATE ${CMAKE_BINARY_DIR}/Debug)

target_include_directories(Demo PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Demo Generic.lib)