cmake_minimum_required(VERSION 3.20)
# Devkitpro includes, don't mind this
if(SWITCH)
    set(PLATFORM NX)
    include(/opt/devkitpro/cmake/Switch.cmake)
    include(/opt/devkitpro/cmake/Platform/NintendoSwitch.cmake)
    include_directories(${DEVKITPRO}/portlibs/switch/include)
endif()

project(hello) # Change this to your project name

set(APP_NAME ${PROJECT_NAME})
set(STAR_INSPECTOR ON) # Enable scene tree inspector? Overrides STAR_IMGUI to ON
set(STAR_IMGUI OFF) # Enable ImGui?

file(GLOB_RECURSE GAME_SOURCE CONFIGURE_DEPENDS "Source/*.cpp")

include(starengine/starengine.cmake)
