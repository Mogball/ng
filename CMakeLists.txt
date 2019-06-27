set(NAME "memes")

cmake_minimum_required(VERSION 3.1.0)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_CXX_FLAGS "-fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   ${PROJECT_CXX_FLAGS} -O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${PROJECT_CXX_FLAGS} -O2 -DNG_RELEASE")

set(BOX2D_DIR "${PROJECT_SOURCE_DIR}/Box2D")
file(GLOB_RECURSE BOX2D_SRC ${BOX2D_DIR}/Box2D/**/*.cpp)
add_library(box2d STATIC ${BOX2D_SRC})
target_include_directories(box2d PUBLIC ${BOX2D_DIR})

set(GLFW_DIR "${PROJECT_SOURCE_DIR}/glfw")
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

add_library(glad "${GLFW_DIR}/deps/glad_gl.c")
target_include_directories(glad PUBLIC "${GLFW_DIR}/deps")

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE NG_SRC "${PROJECT_SOURCE_DIR}/ng/*.cpp")
add_executable(${NAME} ${NG_SRC})
target_link_libraries(${NAME} glfw box2d glad ${OPENGL_gl_LIBRARY})
target_include_directories(${NAME} PUBLIC "${GLFW_DIR}/include")
target_include_directories(${NAME} PUBLIC "${GLFW_DIR}/deps")
target_include_directories(${NAME} PUBLIC "${BOX2D_DIR}")
target_include_directories(${NAME} PUBLIC "${OPENGL_INCLUDE_DIR}")
target_compile_options(${NAME} PUBLIC -save-temps)

file(GLOB_RECURSE NN_SRC "${PROJECT_SOURCE_DIR}/nn/*.cpp")
add_executable(nn ${NN_SRC})
target_compile_options(nn PUBLIC -save-temps)
