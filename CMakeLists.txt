cmake_minimum_required(VERSION 4.2)
project(student_management LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS uuid)

file(GLOB SOURCES "src/*.cpp")

add_executable(student_management ${SOURCES})

# Professional Warning Setup: Applies -Wall -Wextra -Wpedantic safely
target_compile_options(student_management PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

# Teach CMake to find headers inside your local 'include' directory
target_include_directories(student_management PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(student_management PRIVATE Boost::uuid)
