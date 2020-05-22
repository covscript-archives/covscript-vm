cmake_minimum_required(VERSION 3.1)
project(covscript-vm)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/mozart)
include_directories(third-party/mozart/mpp_core)
include_directories(third-party/mozart/mpp_foundation)
include_directories(third-party/mozart/mpp_system)
include_directories(third-party/mozart/mpp_string)

##### Rust library
if (WIN32)
    set(RUST_DEP_SYS_LIBS wsock32 ws2_32 userenv)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CARGO_FLAGS --target "x86_64-pc-windows-gnu")
        set(RUST_WINDOWS_TARGET_DIR "x86_64-pc-windows-gnu/")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(CARGO_FLAGS --target "i686-pc-windows-gnu")
        set(RUST_WINDOWS_TARGET_DIR "i686-pc-windows-gnu/")
    endif()
else ()
    set(RUST_DEP_SYS_LIBS pthread dl)
    set(CARGO_FLAGS "")
    set(RUST_WINDOWS_TARGET_DIR "")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build --package compiler ${CARGO_FLAGS})
    set(RUST_TARGET_NAME "debug")
else ()
    set(CARGO_CMD cargo build --release --package compiler ${CARGO_FLAGS})
    set(RUST_TARGET_NAME "release")
endif ()

set(RUST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party/covscript-rs)
set(RUST_TARGET_DIR ${RUST_SRC_DIR}/target)
set(RUST_BUILD_DIR ${RUST_TARGET_DIR}/${RUST_WINDOWS_TARGET_DIR}${RUST_TARGET_NAME})

set(CBINDGEN_CFG ${CMAKE_CURRENT_SOURCE_DIR}/cbindgen.toml)
set(CBINDGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/cbindgen)
set(CBINDGEN_H ${CBINDGEN_DIR}/rustlib.hpp)
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
set_target_properties(compile-rust PROPERTIES LOCATION ${RUST_TARGET_DIR})
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${RUST_TARGET_DIR})

link_directories(${RUST_BUILD_DIR})
include_directories(${CBINDGEN_DIR})
##### C++ executable
set(SRC src/main.cpp include/csvm/compiler.hpp src/compiler.cpp)

include_directories(include)
add_executable(covscript ${SRC})
add_dependencies(covscript compile-rust)

add_executable(test-variable tests/variable.cpp)

target_link_libraries(covscript mpp_core)
target_link_libraries(covscript mpp_foundation)
target_link_libraries(covscript mpp_system)
target_link_libraries(covscript mpp_string)
target_link_libraries(covscript covscript_compiler)
target_link_libraries(covscript ${RUST_DEP_SYS_LIBS})
target_link_libraries(test-variable mpp_core mpp_foundation)
