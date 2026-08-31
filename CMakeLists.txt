cmake_minimum_required(VERSION 3.26)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Wrap project name in quotes to handle spaces correctly
project("BizzarePhysics" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)