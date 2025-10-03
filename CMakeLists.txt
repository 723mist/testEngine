cmake_minimum_required(VERSION 3.10)
project(VEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

file(GLOB_RECURSE SOURCES
    core/grphics/*.cpp
    core/input/*.cpp
    core/profiler/*.cpp
    core/window/*.cpp
    core/*.cpp

    core/*.h

    core/grphics/*.hpp
    core/input/*.hpp
    core/profiler/*.hpp
    core/window/*.hpp
    core/*.hpp
)

file(GLOB_RECURSE HEADERS
    core/grphics/*.hpp
    core/input/*.hpp
    core/profiler/*.hpp
    core/window/*.hpp
    core/*.hpp
)

add_executable(VEngine
    core/main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(VEngine PRIVATE
    core
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(VEngine PRIVATE
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW::GLEW
)

#add_custom_command(TARGET VEngine POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_SOURCE_DIR}/assets
#    $<TARGET_FILE_DIR:VEngine>/assets
#    COMMENT "Copying resources to build tree"
#)
