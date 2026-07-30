cmake_minimum_required(VERSION 3.20)

project(redis 
    VERSION 0.1.0
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(redus 
    src/main.cpp
    src/command_processor.cpp 
    src/in_memory_store.cpp 
)

target_include_directories(redis 
    PRIVATE 
        $(PROJECT_SOURCE_DIR)/include
)

target_compile_options(redis 
    PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
)