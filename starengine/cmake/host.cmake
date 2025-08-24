function(add_raylib)
    find_package(raylib 5.5)
    if(NOT raylib_FOUND)
        # Didn't find raylib - download it
        FetchContent_Declare(raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib
            GIT_TAG 5.5
            GIT_SHALLOW ON
            GIT_PROGRESS ON
            EXCLUDE_FROM_ALL
        )
        FetchContent_MakeAvailable(raylib)
        include_directories("${raylib_SOURCE_DIR}/src")
    endif()
endfunction()