set (core_source_files
    "src/core.cpp"
    "src/idle_state.cpp"
    "src/woke_state.cpp"
    "src/soil_humidity_check_state.cpp"
    "src/soil_periodic_check_state.cpp"
    "src/irrigate_soil_state.cpp"
    "src/air_humidity_check_state.cpp"
    "src/air_periodic_check_state.cpp"
    "src/irrigate_air_state.cpp"
    "src/wrap_up_state.cpp"
    "src/standard_configuration.cpp")

neide_add_library (core "${core_source_files}")

neide_target_include_directories (core PUBLIC "include")

if(MSVC)
    neide_target_library_compile_options(core PRIVATE /W4 /WX)
else()
    neide_target_library_compile_options(core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()