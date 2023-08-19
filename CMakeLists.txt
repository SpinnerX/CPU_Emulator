cmake_minimum_required(VERSION 3.0.0)
project(CPU_Emulator VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies/formatCpp)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    FormatCpp::FormatCpp
)