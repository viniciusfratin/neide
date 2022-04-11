set (core_source_files
	"src/core.c"
    "src/idle_state.c"
    "src/woke_state.c")

add_library (core "${core_source_files}")

target_include_directories (core PUBLIC "include")

if(MSVC)
	target_compile_options(core PRIVATE /W4 /WX)
else()
	target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()