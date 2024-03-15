cmake_minimum_required(VERSION 3.0.0)
project(CPU_Emulator VERSION 0.1.0 LANGUAGES CXX)

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


if(APPLE)
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
    target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
endif(APPLE)