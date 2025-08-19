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
endif()

target_link_libraries(${APP_NAME} fmt)
