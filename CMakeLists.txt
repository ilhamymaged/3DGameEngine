cmake_minimum_required(VERSION 3.10)
project(GameEngine)

file(GLOB_RECURSE SRC_FILES Src/*.c)
add_executable(${PROJECT_NAME} ${SRC_FILES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(${PROJECT_NAME} PRIVATE 
    Include
    Src
)

add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/cglm)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw cglm)
