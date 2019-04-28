cmake_minimum_required(VERSION 3.1.0)
project(memes)

set(BOX2D_DIR "${PROJECT_SOURCE_DIR}/Box2D")
file(GLOB_RECURSE BOX2D_SRC ${BOX2D_DIR}/Box2D/**/*.cpp)

add_library(box2d STATIC ${BOX2D_SRC})
target_include_directories(box2d PUBLIC ${BOX2D_DIR})
