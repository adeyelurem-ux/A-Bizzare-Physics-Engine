cmake_minimum_required(VERSION 3.26)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Wrap project name in quotes to handle spaces correctly
project("BizzarePhysics" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(${PROJECT_NAME}
        include/engine/maths/Vector.h
        src/dummy.cpp
        include/engine/BPhysics/PhysicsWorld.h
        include/engine/BPhysics/RigidBody2D.h
        src/PhysicsWorld.cpp
        include/engine/maths/EulerIntegrator.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(Sandbox
        sandbox/main.cpp
)

# Link the engine library to the executable
target_link_libraries(Sandbox
        PRIVATE
        ${PROJECT_NAME}
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BizzareTests
        tests/test_collisions.cpp
)

target_link_libraries(BizzareTests
        PRIVATE
        ${PROJECT_NAME}
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(BizzareTests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)