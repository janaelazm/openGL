cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(
    HelloWorld helloworld.cpp 
    Sources/shaderClass.cpp
    Sources/VBO.cpp
    Sources/VAO.cpp 
    Sources/EBO.cpp 
    Sources/stb.cpp 
    Sources/Texture.cpp 
    Sources/Camera.cpp
    )

target_include_directories(HelloWorld PUBLIC "${CMAKE_SOURCE_DIR}/Header Files")

target_link_libraries(HelloWorld PRIVATE fmt::fmt)
target_link_libraries(HelloWorld PRIVATE glfw )
target_link_libraries(HelloWorld PRIVATE glad::glad)