cmake_minimum_required(VERSION 3.10)
project(VEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/cpp/*.cpp
    src/hpp/*.hpp
)

file(GLOB_RECURSE HEADERS
    src/hpp/*.hpp
)

add_executable(VEngine
    src/main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(VEngine PRIVATE
    src
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
