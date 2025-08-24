function(add_raylib)
    message("[star] shallow cloning raylib-nx, this might take some time...")
	FetchContent_Declare(raylib
		GIT_REPOSITORY https://github.com/luizpestana/raylib-nx
		GIT_PROGRESS TRUE
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL)
	FetchContent_MakeAvailable(raylib)
	include_directories("${raylib_SOURCE_DIR}/src")
endfunction()