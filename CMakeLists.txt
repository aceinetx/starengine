cmake_minimum_required(VERSION 3.20)
project(hello) # Change this to your project name

set(APP_NAME ${PROJECT_NAME})

file(GLOB_RECURSE GAME_SOURCE CONFIGURE_DEPENDS "Source/*.cpp")

include(starengine/starengine.cmake)
