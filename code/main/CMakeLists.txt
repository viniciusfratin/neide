set (main_source_files
        "src/main.c")

add_executable (main "${main_source_files}")

target_link_libraries (main LINK_PUBLIC core)