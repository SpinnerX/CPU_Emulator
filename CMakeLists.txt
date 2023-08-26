cmake_minimum_required(VERSION 3.0.0)
project(CPU_Emulator VERSION 0.1.0 LANGUAGES C CXX)

# Setting C++ standard to 20
set(CMAKE_CXX_STANDARD 20)


# This is how we are able to simply just include 
# Ref Link: https://stackoverflow.com/questions/8304190/cmake-with-include-and-source-paths-basic-setup
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/common
    ${PROJECT_SOURCE_DIR}/src
)

# NOTE: GLOB just searches for the specific extensions
# NOTE: As for GLOB_RECURSE, this checks for that pattern if *.cpp is in the subdirectories
# NOTE: GLOB and GLOB_RECURSE are two different keywords

#function(add_sources src_list src_dir)
#    file(GLOB_RECURSE cur_sources ${src_dir}/*.cpp)
#    list(APPEND ${src_list} ${cur_sources})
#endfunction()

#file(
#    GLOB_RECURSE all_src
#    "${PROJECT_SOURCE_DIR}/src/*.cpp"
#)

#set(all_src "")

#add_sources(all_src, ${PROJECT_SOURCE_DIR}/src
#)
#aux_source_directory(${PROJECT_SOURCE_DIR}/src all_src)
#aux_source_directory(${PROJECT_SOURCE_DIR}/src/common all_src2)

set(
    all_src
    "src/CPU.cpp"
    "src/Memory.cpp"
    "src/common/Types.cpp"
)

# Getting gtest to work with cmake...
if(APPLE)
    include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        )

        FetchContent_MakeAvailable(googletest)
endif(APPLE)

if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(dependencies/formatCpp)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${all_src}
)

target_link_libraries(
    ${PROJECT_NAME}
    FormatCpp::FormatCpp
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
    target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
endif(APPLE)