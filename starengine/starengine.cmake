include_directories("starengine/Source")
include_directories("Source")

set(CMAKE_CXX_STANDARD 20) # C++20
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB ENGINE_SOURCE CONFIGURE_DEPENDS "starengine/Source/*.cpp")

#####################################
## DEPENDENCY CONFIGURATION FUNCTIONS
#####################################

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

if(SWITCH)
    set(PLATFORM NX)
    include(/opt/devkitpro/cmake/Switch.cmake)
    include(/opt/devkitpro/cmake/Platform/NintendoSwitch.cmake)
    include_directories(${DEVKITPRO}/portlibs/switch/include)

    include("starengine/cmake/switch.cmake")
else()
    include("starengine/cmake/host.cmake")
endif()

function(add_fmt)
    FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        master
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(fmt)
endfunction()

add_fmt()

######################
## COPY CONTENT TARGET
######################

set(Content_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Content")
set(Content_DESTINATION_DIR "${CMAKE_BINARY_DIR}/Content")

file(COPY ${Content_SOURCE_DIR} DESTINATION ${Content_DESTINATION_DIR})

add_custom_target(copy_content ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Content" "${CMAKE_BINARY_DIR}/Content"
    COMMENT "Copying content from ${Content_SOURCE_DIR} to ${Content_DESTINATION_DIR}"
)

################
## FEATURE SETUP
################

# Setup inspector
if(STAR_INSPECTOR)
    add_compile_definitions("STAR_INSPECTOR")
    set(STAR_IMGUI ON) # Override since inspector needs imgui
endif()

# Setup imgui
if(STAR_IMGUI)
    add_compile_definitions("STAR_IMGUI")
    include_directories("starengine/imgui")
    include_directories("starengine/rlImGui")

    add_library(rlImGui STATIC "starengine/rlImGui/rlImGui.cpp")

    file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS "starengine/imgui/*.cpp")
    add_library(imgui STATIC ${IMGUI_SOURCES})
endif()

###########################
## EXECUTABLE CONFIGURATION
###########################

if(LINUX OR ANDROID AND(NOT SWITCH))
    # Executable configuration for linux
    add_compile_definitions("STAR_PLATFORM_LINUX")
    # Enable sanitizer
    message("Enabling sanitizer")
    add_compile_options(-fsanitize=address -Wall -Werror)
    add_link_options(-fsanitize=address)

    add_raylib()

    file(GLOB PLATFORM_SOURCE CONFIGURE_DEPENDS "starengine/Source/platform/shared/*.cpp")

    add_executable(${APP_NAME} "proj.linux/main.cpp" ${ENGINE_SOURCE} ${PLATFORM_SOURCE} ${GAME_SOURCE})
    target_link_libraries(${APP_NAME} raylib)
    add_dependencies(${APP_NAME} copy_content)
elseif(WIN32)
    # Executable configuration for windows
    add_compile_definitions("STAR_PLATFORM_WINDOWS")

    add_raylib()

    file(GLOB PLATFORM_SOURCE CONFIGURE_DEPENDS "starengine/Source/platform/shared/*.cpp")

    add_executable(${APP_NAME} WIN32 "proj.windows/main.cpp" ${ENGINE_SOURCE} ${PLATFORM_SOURCE} ${GAME_SOURCE})
    target_link_libraries(${APP_NAME} raylib)
    add_dependencies(${APP_NAME} copy_content)
elseif(SWITCH)
    # Executable configuration for nintendo switch 
    add_compile_definitions("STAR_PLATFORM_SWITCH")

    add_raylib()

    file(GLOB PLATFORM_SOURCE CONFIGURE_DEPENDS "starengine/Source/platform/shared/*.cpp")

    add_executable(${APP_NAME} "proj.switch/main.cpp" ${ENGINE_SOURCE} ${PLATFORM_SOURCE} ${GAME_SOURCE})
    target_link_libraries(${APP_NAME} raylib)

    nx_generate_nacp(${APP_NAME}.nacp
        NAME ${APP_NAME}
    )
    nx_create_nro(${APP_NAME}
        NACP ${APP_NAME}.nacp
    )

endif()

target_link_libraries(${APP_NAME} fmt)
if(STAR_IMGUI)
    target_link_libraries(${APP_NAME} rlImGui imgui)
endif()

#############
## RUN TARGET
#############

if(NOT SWITCH)
    add_custom_target(run
        COMMAND ${APP_NAME}
        DEPENDS ${APP_NAME}
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
endif()