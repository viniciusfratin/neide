set (main_source_files
    "src/main.c"
    "src/irrigator.c"
    "src/wrap_up_action.c")

add_executable (main "${main_source_files}")

target_link_libraries (main LINK_PUBLIC core)

if(MSVC)
    target_compile_options(main PRIVATE /W4 /WX)
else()
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()