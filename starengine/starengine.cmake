include_directories("starengine/Source")
include_directories("Source")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB ENGINE_SOURCE CONFIGURE_DEPENDS "starengine/Source/*.cpp")

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        master
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(fmt)

set(Content_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Content")
set(Content_DESTINATION_DIR "${CMAKE_BINARY_DIR}/Content")

file(COPY ${Content_SOURCE_DIR} DESTINATION ${Content_DESTINATION_DIR})

add_custom_target(copy_content ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Content" "${CMAKE_BINARY_DIR}/Content"
    COMMENT "Copying content from ${Content_SOURCE_DIR} to ${Content_DESTINATION_DIR}"
)

if(STAR_INSPECTOR)
    add_compile_definitions("STAR_INSPECTOR")
    set(STAR_IMGUI ON)
endif()

if(STAR_IMGUI)
    add_compile_definitions("STAR_IMGUI")
    include_directories("starengine/imgui")
    include_directories("starengine/rlImGui")

    add_library(rlImGui STATIC "starengine/rlImGui/rlImGui.cpp")

    file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS "starengine/imgui/*.cpp")
    add_library(imgui STATIC ${IMGUI_SOURCES})
endif()

if(LINUX)
    add_compile_definitions("STAR_PLATFORM_LINUX")
    if(NOT ANDROID AND LINUX)
        add_compile_options(-fsanitize=address -Wall -Werror)
        add_link_options(-fsanitize=address)
    endif()

    find_package(raylib 5.5 REQUIRED)
    if(NOT raylib_FOUND)
        FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 5.5
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL)
        FetchContent_MakeAvailable(raylib)
    endif()

    file(GLOB PLATFORM_SOURCE CONFIGURE_DEPENDS "starengine/Source/platform/linux/*.cpp")

    add_executable(${APP_NAME} "proj.linux/main.cpp" ${ENGINE_SOURCE} ${PLATFORM_SOURCE} ${GAME_SOURCE})
    target_link_libraries(${APP_NAME} raylib)
    add_dependencies(${APP_NAME} copy_content)
endif()

target_link_libraries(${APP_NAME} fmt)
if(STAR_IMGUI)
    target_link_libraries(${APP_NAME} rlImGui imgui)
endif()
