cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0026)
  cmake_policy(SET CMP0026 OLD)
endif()

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

if(POLICY CMP0069)
  cmake_policy(SET CMP0069 NEW)
endif()

set(GRIN_MAJOR_VERSION 0)
set(GRIN_MINOR_VERSION 1)
set(GRIN_PATCH_VERSION 4)
set(GRIN_VERSION ${GRIN_MAJOR_VERSION}.${GRIN_MINOR_VERSION}.${GRIN_PATCH_VERSION})
project(grin-demo-storage LANGUAGES C CXX VERSION ${GRIN_VERSION})

option(BUILD_TESTS "Build unit tests" ON)
option(USE_LTO "Using IPO/LTO support for link-time optimization" OFF)

# ------------------------------------------------------------------------------
# setting default cmake type to Release
# ------------------------------------------------------------------------------
set(DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

if(NOT (CMAKE_CXX_COMPILER_LAUNCHER MATCHES "ccache") AND NOT (CMAKE_C_COMPILER_LAUNCHER MATCHES "ccache"))
    find_program(ccache_EXECUTABLE ccache)
    if(ccache_EXECUTABLE)
        set(CMAKE_C_COMPILER_LAUNCHER ${ccache_EXECUTABLE})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${ccache_EXECUTABLE})
        add_custom_target(grin-ccache-stats
            COMMAND ${ccache_EXECUTABLE} --show-stats
        )
    else()
        add_custom_target(grin-ccache-stats
            COMMAND echo "ccache not found."
        )
    endif(ccache_EXECUTABLE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

if (APPLE)
  set(CMAKE_MACOSX_RPATH ON)
else ()
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g")

message(STATUS "[demo-storage] will build in type: ${CMAKE_BUILD_TYPE}")

# ------------------------------------------------------------------------------
# cmake configs
# ------------------------------------------------------------------------------
include(CheckLibraryExists)
include(GNUInstallDirs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ------------------------------------------------------------------------------
# build demo-storage
# ------------------------------------------------------------------------------

find_package(Protobuf REQUIRED)

find_package(glog REQUIRED)

file(GLOB_RECURSE DEMO_GRIN_SRC_FILES "storage/*.cc" "src/*.cc")

message(${DEMO_GRIN_SRC_FILES})

add_library(demo-grin SHARED ${DEMO_GRIN_SRC_FILES})

target_compile_features(demo-grin PUBLIC cxx_std_17)

target_include_directories(demo-grin SYSTEM BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/../include ${Protobuf_INCLUDE_DIRS})

target_link_libraries(demo-grin PUBLIC ${Protobuf_LIBRARIES} glog::glog)

# ------------------------------------------------------------------------------
# complile protobuf to generate cpp files
# ------------------------------------------------------------------------------
set(DST_DIR "${PROJECT_SOURCE_DIR}/src/common/")

list(APPEND PROTO_FLAGS -I${PROJECT_SOURCE_DIR}/../proto/)

file(GLOB PROTO_FILES RELATIVE "${PROJECT_SOURCE_DIR}/../proto" "${PROJECT_SOURCE_DIR}/../proto/*.proto")

set(PROTO_SRCS "")
set(PROTO_HDRS "")

foreach(f ${PROTO_FILES})
    message(STATUS "Found proto - " ${f})
    get_filename_component(FIL_WE ${f} NAME_WE)
    list(APPEND PROTO_SRCS "${DST_DIR}/${FIL_WE}.pb.cc")
    list(APPEND PROTO_HDRS "${DST_DIR}/${FIL_WE}.pb.h")

    execute_process(COMMAND ${Protobuf_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${DST_DIR} ${f})
endforeach()

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

# ------------------------------------------------------------------------------
# complile protobuf to generate cpp files
# ------------------------------------------------------------------------------
set(DST_DIR "${PROJECT_SOURCE_DIR}/src/common/")

list(APPEND PROTO_FLAGS -I${PROJECT_SOURCE_DIR}/../proto/grin_schema)

file(GLOB PROTO_FILES RELATIVE "${PROJECT_SOURCE_DIR}/../proto/grin_schema" "${PROJECT_SOURCE_DIR}/../proto/grin_schema/*.proto")

set(PROTO_SRCS "")
set(PROTO_HDRS "")

foreach(f ${PROTO_FILES})
    message(STATUS "Found proto - " ${f})
    get_filename_component(FIL_WE ${f} NAME_WE)
    list(APPEND PROTO_SRCS "${DST_DIR}/${FIL_WE}.pb.cc")
    list(APPEND PROTO_HDRS "${DST_DIR}/${FIL_WE}.pb.h")

    execute_process(COMMAND ${Protobuf_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${DST_DIR} ${f})
endforeach()

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

# ------------------------------------------------------------------------------
# build tests
# ------------------------------------------------------------------------------
if (BUILD_TESTS)
    file(GLOB TEST_FILES RELATIVE "${PROJECT_SOURCE_DIR}/test" "${PROJECT_SOURCE_DIR}/test/*.cc")

    foreach(f ${TEST_FILES})
        string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${f})
        set(E_NAME ${CMAKE_MATCH_1})
        message(STATUS "Found test for demo storage - " ${E_NAME})
        add_executable(${E_NAME} test/${E_NAME}.cc)
        target_include_directories(${E_NAME} SYSTEM BEFORE PRIVATE ${PROJECT_SOURCE_DIR}/../include ${Protobuf_INCLUDE_DIRS})
        target_link_libraries(${E_NAME} PRIVATE demo-grin Threads::Threads ${CMAKE_DL_LIBS} ${Protobuf_LIBRARIES} glog::glog)
    endforeach()

    file(GLOB C_TEST_FILES RELATIVE "${PROJECT_SOURCE_DIR}/test" "${PROJECT_SOURCE_DIR}/test/*.c")

    foreach(f ${C_TEST_FILES})
        string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${f})
        set(E_NAME ${CMAKE_MATCH_1})
        message(STATUS "Found C test for demo storage - " ${E_NAME})
        add_executable(C_${E_NAME} test/${E_NAME}.c)
        target_include_directories(C_${E_NAME} SYSTEM BEFORE PRIVATE ${PROJECT_SOURCE_DIR}/../include ${Protobuf_INCLUDE_DIRS})
        target_link_libraries(C_${E_NAME} PRIVATE demo-grin Threads::Threads ${CMAKE_DL_LIBS} ${Protobuf_LIBRARIES} glog::glog)
    endforeach()
endif()

# ------------------------------------------------------------------------------
# Format code & cpplint
# ------------------------------------------------------------------------------
file(GLOB_RECURSE FILES_NEED_FORMAT "storage/*.h" "storage/*.cc"
                                    "src/*.h" "src/*.cc"
                                    "test/*.h" "test/*.cc")
list(REMOVE_ITEM FILES_NEED_FORMAT 
    "${PROJECT_SOURCE_DIR}/src/common/graph.pb.h" 
    "${PROJECT_SOURCE_DIR}/src/common/graph.pb.cc" 
    "${PROJECT_SOURCE_DIR}/src/common/data_type.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/data_type.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/schema.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/schema.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/partition.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/partition.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/storage.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/storage.pb.cc")
    
file(GLOB_RECURSE FILES_NEED_LINT "storage/*.h" "storage/*.cc"
                                  "src/*.h" "src/*.cc"
                                  "test/*.h" "test/*.cc")
list(REMOVE_ITEM FILES_NEED_LINT 
    "${PROJECT_SOURCE_DIR}/src/common/graph.pb.h" 
    "${PROJECT_SOURCE_DIR}/src/common/graph.pb.cc" 
    "${PROJECT_SOURCE_DIR}/src/common/data_type.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/data_type.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/schema.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/schema.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/partition.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/partition.pb.cc"
    "${PROJECT_SOURCE_DIR}/src/common/storage.pb.h"
    "${PROJECT_SOURCE_DIR}/src/common/storage.pb.cc")

add_custom_target(grin-clformat
                  COMMAND clang-format-8 --style=file -i ${FILES_NEED_FORMAT}
                  COMMENT "Running clang-format."
                  VERBATIM)

add_custom_target(grin-cpplint
        COMMAND ${PROJECT_SOURCE_DIR}/misc/cpplint.py --root=${PROJECT_SOURCE_DIR} ${FILES_NEED_LINT}
        COMMENT "Running cpplint check."
        VERBATIM)
