cmake_minimum_required(VERSION 3.20)

project(redis_clone
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(redis_core
    src/in_memory_store.cpp
    src/command_processor.cpp
)

target_include_directories(redis_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(redis_core
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(redis_clone
    src/main.cpp
)

target_link_libraries(redis_clone
    PRIVATE
        redis_core
)

target_compile_options(redis_clone
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(redis_tests
    tests/test_main.cpp
    tests/test_in_memory_store.cpp
    tests/test_command_processor.cpp
)

target_link_libraries(redis_tests
    PRIVATE
        redis_core
)

target_compile_options(redis_tests
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

enable_testing()

add_test(
    NAME redis_tests
    COMMAND redis_tests
)