cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Qt)
project(${PROJECT_NAME})

set(source_dir "${PROJECT_SOURCE_DIR}")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_NAME}
        ${source_dir} ${source_dir}/Root)

# find all .h and .cpp files:
file(GLOB_RECURSE cpp_files ${source_dir}/Root/*.cpp)
file(GLOB_RECURSE h_files ${source_dir}/Root/*.h)

message(${source_dir})
#add_compile_definitions(CLION)
add_executable(${PROJECT_NAME} ${cpp_files} ${h_files} main.cpp)

