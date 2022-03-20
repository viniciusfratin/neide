set (core_source_files
        "src/core.c")

add_library (core "${core_source_files}")

target_include_directories (core PUBLIC "include")