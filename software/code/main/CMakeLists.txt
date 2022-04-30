set (main_source_files
    "src/main.c"
    "src/irrigator.c"
    "src/wrap_up_action.c")

neide_add_executable (main "${main_source_files}")

neide_target_link_libraries (main LINK_PUBLIC core)

if(MSVC)
    neide_target_executable_compile_options(main PRIVATE /W4 /WX)
else()
    neide_target_executable_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()