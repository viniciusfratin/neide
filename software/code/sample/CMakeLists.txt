set (sample_source_files
    "src/main.c"
    "src/irrigator.c"
    "src/wrap_up_action.c")

neide_add_executable (sample "${sample_source_files}")

neide_target_include_directories (sample PRIVATE "src")

neide_target_link_libraries (sample LINK_PRIVATE core)

if(MSVC)
    neide_target_executable_compile_options(sample PRIVATE /W4 /WX)
else()
    neide_target_executable_compile_options(sample PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()