cmake_minimum_required(VERSION 3.16)
project(covscript-vm)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/mozart)
include_directories(third-party/mozart)

##### Rust library
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build --package compiler)
    set(RUST_TARGET_NAME "debug")
else ()
    set(CARGO_CMD cargo build --release --package compiler)
    set(RUST_TARGET_NAME "release")
endif ()

set(RUST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/covscript-rs)
set(RUST_BUILD_DIR ${RUST_SRC_DIR}/target/${RUST_TARGET_NAME})

set(CBINDGEN_CFG ${CMAKE_CURRENT_SOURCE_DIR}/cbindgen.toml)
set(CBINDGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/cbindgen)
set(CBINDGEN_H ${CBINDGEN_DIR}/covscript_compiler.hpp)
set(CBINDGEN_CMD cbindgen --config ${CBINDGEN_CFG} --crate compiler --output ${CBINDGEN_H})

message(STATUS "[Rust]: Rust src dir: ${RUST_SRC_DIR}")
message(STATUS "[Rust]: Rust build dir: ${RUST_BUILD_DIR}")
message(STATUS "[Rust]: cbindgen config: ${CBINDGEN_CFG}")
message(STATUS "[Rust]: cbindgen header: ${CBINDGEN_H}")

add_custom_target(compile-rust ALL
        COMMENT "Compiling Rust module"
        COMMAND ${CBINDGEN_CMD}
        COMMAND ${CARGO_CMD}
        WORKING_DIRECTORY ${RUST_SRC_DIR})
set_target_properties(compile-rust PROPERTIES LOCATION ${RUST_BUILD_DIR})

link_directories(${RUST_BUILD_DIR})
include_directories(${CBINDGEN_DIR})
##### C++ executable
set(SRC main.cpp)

add_executable(covscript ${SRC})
add_dependencies(covscript compile-rust)

target_link_libraries(covscript mpp_core)
target_link_libraries(covscript mpp_foundation)
target_link_libraries(covscript mpp_system)
target_link_libraries(covscript mpp_string)
target_link_libraries(covscript covscript_compiler)
