cmake_minimum_required(VERSION 3.0.0)
project(CPU_Emulator VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

add_subdirectory(dependencies/formatCpp)

add_executable(
    ${PROJECT_NAME}
    main.cpp

    CPU_Emulator/src/Memory.cpp
    CPU_Emulator/src/CPU.cpp


    # In correct order
    CPU_Emulator/include/common.h
    CPU_Emulator/include/Memory.h
    CPU_Emulator/include/CPU.h
)

target_link_libraries(
    ${PROJECT_NAME}
    FormatCpp::FormatCpp
)
