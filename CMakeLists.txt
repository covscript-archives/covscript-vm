cmake_minimum_required(VERSION 3.16)
project(covscript_vm)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/mozart)
include_directories(third-party/mozart)

add_executable(covscript_vm main.cpp)
target_link_libraries(covscript_vm mpp_core)
target_link_libraries(covscript_vm mpp_foundation)
target_link_libraries(covscript_vm mpp_system)
target_link_libraries(covscript_vm mpp_string)
